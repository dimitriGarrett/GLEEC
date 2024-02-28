#include "FrameManager.h"

#include "GPUManager.h"
#include "RenderTargetManager.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/PipelineBarrier.h"
#include "Internal/Graphics/vk/Image/TransitionImage.h"
#endif

#include "math/rand/rand.h"

namespace GLEEC::Graphics
{
    std::array<Frame, GLEEC_WINDOW_MAX_WINDOWS> FrameManager::frames = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    bool FrameManager::justRendered = true;

    std::bitset<GLEEC_WINDOW_MAX_WINDOWS> FrameManager::recreateFlags = { 0 };

#if GLEEC_USE_FRAMES_IN_FLIGHT
    uint32_t FrameManager::activeFrame = 0;
    uint32_t FrameManager::lastFrame = 0;

    std::array<Internal::Graphics::vk::Fence,
        Frame::FRAMES_IN_FLIGHT> FrameManager::fences = {};
#else
    Internal::Graphics::vk::Fence FrameManager::fence = {};
#endif
#endif

    void FrameManager::initFrame(size_t i)
    {
        Window::Window& window = Window::WindowManager::windows[i];

#if GLEEC_USE_FRAMES_IN_FLIGHT
#define ACCESS_FRAME data
#else
#define ACCESS_FRAME frame.frame
#endif

#if GLEEC_USE_FRAMES_IN_FLIGHT
        for (FrameData& data : frames[i].frames)
        {
#else
        Frame& frame = frames[i];
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            ACCESS_FRAME.commandPool = Internal::Graphics::vk::createCommandPool(
                GPUManager::activeGPU.device,
                GPUManager::activeGPU.graphicsQueue.index);

            ACCESS_FRAME.commandBuffer = Internal::Graphics::vk::allocateCommandBuffer(
                GPUManager::activeGPU.device,
                Internal::Graphics::vk::commandBufferAllocateInfo(
                    ACCESS_FRAME.commandPool));

            ACCESS_FRAME.swapchainSemaphore = Internal::Graphics::vk::createSemaphore(
                GPUManager::activeGPU.device);
            ACCESS_FRAME.renderSemaphore = Internal::Graphics::vk::createSemaphore(
                GPUManager::activeGPU.device);

            ACCESS_FRAME.submitInfo.commandBuffer =
                Internal::Graphics::vk::commandBufferSubmitInfo(ACCESS_FRAME.commandBuffer);

            // signal this after the color attachment has been written to
            ACCESS_FRAME.submitInfo.waitSemaphore =
                Internal::Graphics::vk::semaphoreSubmitInfo(
                    ACCESS_FRAME.renderSemaphore, VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR);

            // wait until the color attachment is ready,
            // and triggers after the fragment shader is done,
            // which is when you can draw it
            ACCESS_FRAME.submitInfo.signalSemaphore =
                Internal::Graphics::vk::semaphoreSubmitInfo(
                    ACCESS_FRAME.swapchainSemaphore, VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT);

            ACCESS_FRAME.submitInfo.submit =
                Internal::Graphics::vk::submitInfo2(
                    ACCESS_FRAME.submitInfo.commandBuffer,
                    ACCESS_FRAME.submitInfo.waitSemaphore,
                    ACCESS_FRAME.submitInfo.signalSemaphore);
#endif

#if GLEEC_USE_FRAMES_IN_FLIGHT
        }
#endif

        frames[i].clearColor = { {
            math::rand::uniform_unit_interval::generatef<math::rand::xoshiro256plusplus>(),
            math::rand::uniform_unit_interval::generatef<math::rand::xoshiro256plusplus>(),
            math::rand::uniform_unit_interval::generatef<math::rand::xoshiro256plusplus>(),
            1.0f
        }};
    }

    void FrameManager::destroyFrame(size_t i)
    {
        // wait to delete stuff until the GPU isn't using them
        GPUManager::activeGPU.wait();

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        recreateFlags[i] = false;

#if GLEEC_USE_FRAMES_IN_FLIGHT
        for (FrameData& data : frames[i].frames)
        {
#else
        Frame& frame = frames[i];
#endif

            Internal::Graphics::vk::destroyCommandPool(
                GPUManager::activeGPU.device, ACCESS_FRAME.commandPool);

            Internal::Graphics::vk::destroySemaphore(
                GPUManager::activeGPU.device, ACCESS_FRAME.swapchainSemaphore);

            Internal::Graphics::vk::destroySemaphore(
                GPUManager::activeGPU.device, ACCESS_FRAME.renderSemaphore);

            ACCESS_FRAME.commandPool = VK_NULL_HANDLE;
            ACCESS_FRAME.swapchainSemaphore = VK_NULL_HANDLE;
            ACCESS_FRAME.renderSemaphore = VK_NULL_HANDLE;
#if GLEEC_USE_FRAMES_IN_FLIGHT
        }
#endif

#endif
    }

    void FrameManager::beginFrame(size_t i)
    {
        Window::Window& window = Window::WindowManager::windows[i];

        Frame& frame = frames[i];

#if GLEEC_USE_FRAMES_IN_FLIGHT
        FrameData& data = frame.frames[activeFrame];
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        /* swapchain update */
        /* frame.swapchainImageIndex = Internal::Graphics::vk::acquireNextImage(
            GPUManager::activeGPU.device, window.swapchain, UINT64_MAX,
            ACCESS_FRAME.swapchainSemaphore, nullptr); */

        VkAcquireNextImageInfoKHR imageInfo =
            Internal::Graphics::vk::acquireNextImageInfo(
                window.swapchain, UINT64_MAX, ACCESS_FRAME.swapchainSemaphore);

        VkResult result = Internal::Graphics::vk::acquireNextImage2(
            GPUManager::activeGPU.device, &imageInfo, &frame.swapchainImageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR)
        {
            recreateFrame(i);

            return;
        }

        CHECK_VK(result);

        /* swapchain update */

        /* command pool reset */
        Internal::Graphics::vk::resetCommandPool(
            GPUManager::activeGPU.device, ACCESS_FRAME.commandPool);
        /* command pool reset */

        /* begin command buffer */
        Internal::Graphics::vk::beginCommandBufferOneTimeSubmit(
            ACCESS_FRAME.commandBuffer);
        /* begin command buffer */

        /* image transition */
        Internal::Graphics::vk::Image& image = RenderTargetManager::renderTargets[i].image;

        Internal::Graphics::vk::transitionColorImageUndefinedToGeneral(
            ACCESS_FRAME.commandBuffer, image);
        /* image transition */

        /* clear image */
        static const VkImageSubresourceRange clearRange = 
            { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        vkCmdClearColorImage(ACCESS_FRAME.commandBuffer, image, VK_IMAGE_LAYOUT_GENERAL,
            &frame.clearColor, 1, &clearRange);
        /* clear image */
#endif
    }

    void FrameManager::endFrame(size_t i)
    {
        Window::Window& window = Window::WindowManager::windows[i];

        Frame& frame = frames[i];

#if GLEEC_USE_FRAMES_IN_FLIGHT
        FrameData& data = frame.frames[activeFrame];
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        /* image transition */
        Internal::Graphics::vk::Image& drawImage =
            RenderTargetManager::renderTargets[i].image;

        Internal::Graphics::vk::transitionColorImageGeneralToTransferSrc(
            ACCESS_FRAME.commandBuffer, drawImage);

        VkImage& image = window.swapchain.images[frame.swapchainImageIndex];

        Internal::Graphics::vk::transitionColorImageUndefinedToTransferDst(
            ACCESS_FRAME.commandBuffer, image);

        VkExtent3D extent = { 0, 0, 1 };
        extent.width = static_cast<uint32_t>(window.size().x);
        extent.height = static_cast<uint32_t>(window.size().y);

        VkBlitImageInfo2 blitInfo =
            Internal::Graphics::vk::imageBlitInfo(
                Internal::Graphics::vk::colorImageBlit(
                    RenderTargetManager::renderTargets[i].image.extent,
                    window.swapchain.extent),
                drawImage, image);

        Internal::Graphics::vk::blitImage(ACCESS_FRAME.commandBuffer, blitInfo);

        Internal::Graphics::vk::transitionColorImageTransferDstToPresentSrc(
            ACCESS_FRAME.commandBuffer, image);
        /* image transition */

        /* end command buffer */
        Internal::Graphics::vk::endCommandBuffer(ACCESS_FRAME.commandBuffer);
        /* end command buffer */
#endif
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    inline bool FrameManager::batchSubmits()
    {
        std::vector<VkSubmitInfo2> submissions = {};

        for (size_t i : Window::WindowManager::renderableWindowIndices())
        {
            VkSubmitInfo2& info = submissions.emplace_back();

#if GLEEC_USE_FRAMES_IN_FLIGHT
            info = frames[i].frames[activeFrame].submitInfo.submit;
#else
            info = frames[i].frame.submitInfo.submit;
#endif
        }

        if (submissions.empty()) return false;

        justRendered = true;

#if !defined(_MSVC_LANG)
        CHECK_VK(vkQueueSubmit2(
            GPUManager::activeGPU.graphicsQueue,
            static_cast<uint32_t>(submissions.size()),

#if GLEEC_USE_FRAMES_IN_FLIGHT
            submissions.data(), fences[activeFrame]));
#else
            submissions.data(), fence));
#endif
#else
            // msvc hates me
#if GLEEC_USE_FRAMES_IN_FLIGHT
        CHECK_VK(vkQueueSubmit2(
            GPUManager::activeGPU.graphicsQueue,
            static_cast<uint32_t>(submissions.size()),
            submissions.data(), fences[activeFrame]));
#else
        CHECK_VK(vkQueueSubmit2(
            GPUManager::activeGPU.graphicsQueue,
            static_cast<uint32_t>(submissions.size()),
            submissions.data(), fence));
#endif
#endif

        return true;
    }

    inline void FrameManager::batchPresents()
    {
        VkPresentInfoKHR presentInfo = {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR
        };

        std::vector<VkSemaphore> semaphores = {};
        std::vector<VkSwapchainKHR> swapchains = {};
        std::vector<uint32_t> swapchainImages = {};

        std::vector<VkResult> results = {};

        for (Window::Window* window : Window::WindowManager::renderableWindows())
        {
            Frame& frame = frames[Window::WindowManager::findWindowIndex(window)];

#if GLEEC_USE_FRAMES_IN_FLIGHT
            semaphores.push_back(frame.frames[activeFrame].renderSemaphore);
#else
            semaphores.push_back(frame.frame.renderSemaphore);
#endif

            swapchains.push_back(window->swapchain.swapchain);
            swapchainImages.push_back(frame.swapchainImageIndex);

            ++presentInfo.waitSemaphoreCount;
            ++presentInfo.swapchainCount;

            results.push_back(VK_SUCCESS);
        }

        presentInfo.pWaitSemaphores = semaphores.data();
        presentInfo.pSwapchains = swapchains.data();
        presentInfo.pImageIndices = swapchainImages.data();

        presentInfo.pResults = results.data();

        Internal::Graphics::vk::queuePresent(
            GPUManager::activeGPU.graphicsQueue, presentInfo);

        for (int i = 0; i < presentInfo.swapchainCount; ++i)
        {
            if (presentInfo.pResults[i] == VK_ERROR_OUT_OF_DATE_KHR)
            {
                recreateFrame(i);
            }
        }
    }
#endif

    void FrameManager::begin()
    {
        // if nothing was rendered, don't wait on the fences,
        // it just blocks forever when iconifying
        if (justRendered)
        {
#if GLEEC_USE_FRAMES_IN_FLIGHT
            Internal::Graphics::vk::waitForFence(
                GPUManager::activeGPU.device, fences[lastFrame]);
            Internal::Graphics::vk::resetFence(
                GPUManager::activeGPU.device, fences[lastFrame]);
#else
            Internal::Graphics::vk::waitForFence(
                GPUManager::activeGPU.device, fence);
            Internal::Graphics::vk::resetFence(
                GPUManager::activeGPU.device, fence);
#endif
        }

        justRendered = false;

        for (size_t i : Window::WindowManager::renderableWindowIndices())
        {
            if (recreateFlags[i])
            {
                recreateFlags[i] = false;

                recreateFrameInternal(i);
            }

            beginFrame(i);
        }
    }

    void FrameManager::end()
    {
        for (size_t i : Window::WindowManager::renderableWindowIndices())
        {
            if (recreateFlags[i])
            {
                recreateFlags[i] = false;

                recreateFrameInternal(i);
            }

            endFrame(i);
        }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        // batch all the presentations and submissions
        if (batchSubmits())
            batchPresents();
#endif

#if GLEEC_USE_FRAMES_IN_FLIGHT
        lastFrame = activeFrame;
        activeFrame = (activeFrame + 1) % Frame::FRAMES_IN_FLIGHT;
#endif
    }

    void FrameManager::recreateFrameInternal(size_t i)
    {
        // this shouldn't be needed, but including just to be safe
        // (shouldn't need to be included because we already waited
        // for the fences to be signalled, so the resources are
        // free again and not used)
        GPUManager::activeGPU.wait();
        // just want to be safe

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Window::Window& window = Window::WindowManager::windows[i];

        Internal::Graphics::vk::Swapchain& swapchain = window.swapchain;

        Internal::Graphics::vk::destroySwapchainResources(
            GPUManager::activeGPU.device, swapchain);

        VkSwapchainCreateInfoKHR swapchainInfo = swapchain.createInfo;

        VkSwapchainKHR oldSwapchain = swapchain;

        auto caps = Internal::Graphics::vk::getPhysicalDeviceSurfaceCapabilities(
            GPUManager::activeGPU.device.physicalDevice, window.surface);

        swapchainInfo.imageExtent = caps.currentExtent;
        swapchainInfo.oldSwapchain = swapchain;

        swapchain =
            Internal::Graphics::vk::createSwapchain(
                GPUManager::activeGPU.device, window.surface, swapchainInfo);

        Internal::Graphics::vk::destroySwapchain(
            GPUManager::activeGPU.device, oldSwapchain);

        // if the actual image got resized, then recreate the render target
        // (dont want to render into a too big or too small image, might 
        // lead to some artifacts?) (i think)
        if (swapchain.scalingMethod == 0)
        {
            RenderTargetManager::recreateRenderTarget(i);
        }
#endif
    }
}
