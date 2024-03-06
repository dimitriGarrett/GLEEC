#include "RenderTargetManager.h"
#include "GPUManager.h"

namespace GLEEC::Graphics
{
    std::array<RenderTarget, GLEEC_WINDOW_MAX_WINDOWS> RenderTargetManager::renderTargets = {};

    void RenderTargetManager::initRenderTarget(size_t i)
    {
        Window::Window& window = Window::WindowManager::windows[i];
        RenderTarget& renderTarget = renderTargets[i];

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkExtent3D extent = {};
        extent.width = static_cast<uint32_t>(window.size().x);
        extent.height = static_cast<uint32_t>(window.size().y);
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

    void RenderTargetManager::swap(size_t a, size_t b)
    {
        RenderTarget& ra = renderTargets[a];
        RenderTarget& rb = renderTargets[b];

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        std::swap(ra.imageView, rb.imageView);

        std::swap(ra.image.image, rb.image.image);
        std::swap(ra.image.allocation, rb.image.allocation);
        std::swap(ra.image.extent, rb.image.extent);
        std::swap(ra.image.format, rb.image.format);
#endif
    }
}
