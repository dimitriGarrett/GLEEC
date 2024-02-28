#pragma once

#include "Internal/Graphics/Backend.h"
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Image.h"
#include "Internal/Graphics/vk/ImageView.h"
#else
#error "Unknown Graphics backend for GLEEC!"
#endif

namespace GLEEC::Graphics
{
    // mainly for HDR and post processing (blah blah blah)
    // for vulkan cause idk if dx12 needs this but vk does
    struct RenderTarget
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Image image = {};
        Internal::Graphics::vk::ImageView imageView = {};
#endif
    };
}
