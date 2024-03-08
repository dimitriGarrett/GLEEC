#pragma once

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Image.h"
#endif

namespace GLEEC::Graphics
{
    struct Texture
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Image image = {};
#endif

        std::string filepath = "";
    };
}
