#include "RenderTargetManager.h"
#include "FrameManager.h"

#include "Core/Graphics/GPUManager.h"

namespace GLEEC::Graphics
{
    std::array<RenderTarget, GLEEC_WINDOW_MAX_WINDOWS> RenderTargetManager::renderTargets = {};

    void RenderTargetManager::initRenderTarget(size_t i)
    {
        Window::Window& window = Window::WindowManager::windows[i];
        RenderTarget& renderTarget = renderTargets[i];

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        math::ivec2 size = Window::WindowManager::Get::size(window);

        VkExtent3D extent = {};
        extent.width = static_cast<uint32_t>(size.x);
        extent.height = static_cast<uint32_t>(size.y);
        extent.depth = 1;

        static VkImageCreateInfo imageCreateInfo =
            Internal::Graphics::vk::image2D(
                VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                VK_IMAGE_USAGE_STORAGE_BIT |
                VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

                VK_FORMAT_R16G16B16A16_SFLOAT,
                VkExtent3D{});

        imageCreateInfo.extent = extent;

        renderTarget.image =
            Internal::Graphics::vk::createImage(
                GPUManager::activeGPU.allocator, imageCreateInfo);

        renderTarget.imageView =
            Internal::Graphics::vk::createColorImageView2D(
                GPUManager::activeGPU.device,
                renderTarget.image,
                renderTarget.image.format);

        VkRect2D renderArea = {};
        renderArea.extent.width = extent.width;
        renderArea.extent.height = extent.height;

        VkRenderingInfo& info = (renderTarget.renderingInfo = {
            VK_STRUCTURE_TYPE_RENDERING_INFO,
        });

        info.renderArea = renderArea;

        info.layerCount = 1;
        info.colorAttachmentCount = 1;
        info.pColorAttachments = &renderTarget.colorAttachment;

        VkRenderingAttachmentInfo& colorAttachment = (renderTarget.colorAttachment = {
            VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO
        });

        colorAttachment.imageView = renderTarget.imageView;
        colorAttachment.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

        colorAttachment.clearValue.color = window.clearColor;
        colorAttachment.clearValue.depthStencil = window.clearDepth;
#endif
    }

    void RenderTargetManager::destroyRenderTarget(size_t i)
    {
        RenderTarget& renderTarget = renderTargets[i];

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        if (renderTarget.image.image == VK_NULL_HANDLE) return;

        Internal::Graphics::vk::destroyImage(
            GPUManager::activeGPU.allocator, renderTarget.image);

        Internal::Graphics::vk::destroyImageView(
            GPUManager::activeGPU.device, renderTarget.imageView);

        renderTarget.image.allocation = VK_NULL_HANDLE;
        renderTarget.image.image = VK_NULL_HANDLE;
        renderTarget.imageView = VK_NULL_HANDLE;
#endif
    }

    void RenderTargetManager::begin()
    {
        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            RenderTarget& target = renderTargets.at(i);
            FrameData& frame = FrameManager::frame(i);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::transitionColorImageUndefinedToColorAttachment(
                frame.commandBuffer, target.image);

            vkCmdBeginRendering(frame.commandBuffer, &target.renderingInfo);
#endif
        }
    }

    void RenderTargetManager::end()
    {
        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            RenderTarget& target = renderTargets.at(i);
            FrameData& frame = FrameManager::frame(i);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            vkCmdEndRendering(frame.commandBuffer);

            Internal::Graphics::vk::transitionColorImageColorAttachmentToTransferSrc(
                frame.commandBuffer, target.image);

            Window::WindowManager::end(i);
#endif
        }
    }
}
