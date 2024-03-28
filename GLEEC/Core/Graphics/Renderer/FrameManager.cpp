#include "FrameManager.h"
#include "RenderTargetManager.h"
#include "RenderStateManager.h"
#include "ShaderResourceManager.h"

#include "Core/Graphics/GPUManager.h"

namespace GLEEC::Graphics
{
    std::array<Frame, GLEEC_WINDOW_MAX_WINDOWS> FrameManager::frames = {};

#if GLEEC_USE_FRAMES_IN_FLIGHT
    uint32_t FrameManager::activeFrame = 0;
    uint32_t FrameManager::lastFrame = 0;
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#if GLEEC_USE_FRAMES_IN_FLIGHT
    std::array<Internal::Graphics::vk::Fence, Frame::FRAMES_IN_FLIGHT>
        FrameManager::fences = {};
#else
    Internal::Graphics::vk::Fence FrameManager::fence = {};
#endif
#endif

    bool FrameManager::justRendered = true;

    inline FrameData& FrameManager::frame(size_t i)
    {
#if GLEEC_USE_FRAMES_IN_FLIGHT
        return frames[i].frames[activeFrame];
#else
        return frames[i].frame;
#endif
    }

    inline void FrameManager::init()
    {
        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            initFrame(i);
        }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#if GLEEC_USE_FRAMES_IN_FLIGHT
        fences[0] = Internal::Graphics::vk::createSignaledFence(
            GPUManager::activeGPU.device);

        for (size_t i = 1; i < fences.size(); ++i)
        {
            fences[i] = Internal::Graphics::vk::createFence(
                GPUManager::activeGPU.device);
        }
#else
        fence = Internal::Graphics::vk::createSignaledFence(
            GPUManager::activeGPU.device);
#endif
#endif
    }

    inline void FrameManager::destroy()
    {
        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            destroyFrame(i);
        }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#if GLEEC_USE_FRAMES_IN_FLIGHT
        for (Internal::Graphics::vk::Fence& fence : fences)
        {
#endif
            Internal::Graphics::vk::destroyFence(
                GPUManager::activeGPU.device, fence);
#if GLEEC_USE_FRAMES_IN_FLIGHT
        }
#endif
#endif
    }

    void FrameManager::initFrame(size_t i)
    {
#if GLEEC_USE_FRAMES_IN_FLIGHT
        for (FrameData& frame : frames[i].frames)
        {
#else
            FrameData& frame = frames[i].frame;
#endif

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            frame.commandPool = Internal::Graphics::vk::createCommandPool(
                GPUManager::activeGPU.device,
                GPUManager::activeGPU.graphicsQueue.index);

            frame.commandBuffer = Internal::Graphics::vk::allocateCommandBuffer(
                GPUManager::activeGPU.device,
                Internal::Graphics::vk::commandBufferAllocateInfo(
                    frame.commandPool));

            frame.swapchainSemaphore = Internal::Graphics::vk::createSemaphore(
                GPUManager::activeGPU.device);
            frame.renderSemaphore = Internal::Graphics::vk::createSemaphore(
                GPUManager::activeGPU.device);

            frame.submitInfo.commandBuffer =
                Internal::Graphics::vk::commandBufferSubmitInfo(frame.commandBuffer);

            // signal this after the color attachment has been written to
            frame.submitInfo.waitSemaphore =
                Internal::Graphics::vk::semaphoreSubmitInfo(
                    frame.renderSemaphore, VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR);

            // wait until the color attachment is ready,
            // and triggers after the fragment shader is done,
            // which is when you can draw it
            frame.submitInfo.signalSemaphore =
                Internal::Graphics::vk::semaphoreSubmitInfo(
                    frame.swapchainSemaphore, VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT);

            frame.submitInfo.submit =
                Internal::Graphics::vk::submitInfo2(
                    frame.submitInfo.commandBuffer,
                    frame.submitInfo.waitSemaphore,
                    frame.submitInfo.signalSemaphore);
#endif

#if GLEEC_USE_FRAMES_IN_FLIGHT
        }
#endif
    }

    void FrameManager::destroyFrame(size_t i)
    {
        // because of the window manager stuff
        GPUManager::activeGPU.wait();

#if GLEEC_USE_FRAMES_IN_FLIGHT
        for (FrameData& frame : frames[i].frames)
        {
#else
            FrameData& frame = frames[i].frame;
#endif
            Internal::Graphics::vk::destroyCommandPool(
                GPUManager::activeGPU.device, frame.commandPool);

            Internal::Graphics::vk::destroySemaphore(
                GPUManager::activeGPU.device, frame.swapchainSemaphore);

            Internal::Graphics::vk::destroySemaphore(
                GPUManager::activeGPU.device, frame.renderSemaphore);

            frame.commandPool = VK_NULL_HANDLE;
            frame.commandBuffer = VK_NULL_HANDLE;
            frame.swapchainSemaphore = VK_NULL_HANDLE;
            frame.renderSemaphore = VK_NULL_HANDLE;
#if GLEEC_USE_FRAMES_IN_FLIGHT
        }
#endif
    }

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

        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            FrameData& frameData = frame(i);

            ShaderResourceManager::bind(frameData);
            
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::resetCommandPool(
                GPUManager::activeGPU.device, frameData.commandPool);

            Internal::Graphics::vk::beginCommandBufferOneTimeSubmit(
                frameData.commandBuffer);
#endif

            RenderStateManager::prepareState(frameData, i);
        }
    }

    void FrameManager::end()
    {
        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            FrameData& frameData = frame(i);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::endCommandBuffer(frameData.commandBuffer);
#endif
        }

        if (batchSubmits())
        {
            batchPresents();
        }

#if GLEEC_USE_FRAMES_IN_FLIGHT
        lastFrame = activeFrame;
        activeFrame = (activeFrame + 1) % Frame::FRAMES_IN_FLIGHT;
#endif
    }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    bool FrameManager::batchSubmits()
    {
        std::vector<VkSubmitInfo2> submits = {};

        for (size_t i : Window::WindowManager::availableWindows())
        {
            submits.push_back(frame(i).submitInfo.submit);
        }

        if (submits.empty()) return false;

        justRendered = true;

#if GLEEC_USE_FRAMES_IN_FLIGHT
        CHECK_VK(vkQueueSubmit2(
            GPUManager::activeGPU.graphicsQueue,
            static_cast<uint32_t>(submits.size()),
            submits.data(), fences[activeFrame]));
#else
        CHECK_VK(vkQueueSubmit2(
            GPUManager::activeGPU.graphicsQueue,
            static_cast<uint32_t>(submits.size()),
            submits.data(), fence));
#endif

        return true;
    }

    void FrameManager::batchPresents()
    {
        uint32_t size = Window::WindowManager::availableWindows().size();

        std::vector<VkSemaphore> semaphores = {};
        std::vector<VkSwapchainKHR> swapchains = {};
        std::vector<uint32_t> indices = {};

        std::vector<VkResult> results = {};

        VkPresentInfoKHR presentInfo = {
            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            nullptr,
            size,
            nullptr,
            size,
        };

        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            FrameData& frameData = frame(i);

            semaphores.push_back(frameData.renderSemaphore);

            swapchains.push_back(Window::WindowManager::windows[i].swapchain);
            indices.push_back(Window::WindowManager::windows[i].swapchainImageIndex);

            results.emplace_back(VK_SUCCESS);
        }

        presentInfo.pWaitSemaphores = semaphores.data();
        presentInfo.pSwapchains = swapchains.data();
        presentInfo.pImageIndices = indices.data();
        presentInfo.pResults = results.data();

        Internal::Graphics::vk::queuePresent(
            GPUManager::activeGPU.graphicsQueue, presentInfo);

        for (uint32_t i = 0; i < size; ++i)
        {
            if (presentInfo.pResults[i] == VK_ERROR_OUT_OF_DATE_KHR)
            {
                Window::WindowManager::recreate(i);
            }
        }
    }
#endif
}
