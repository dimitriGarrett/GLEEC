#pragma once

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Shader.h"
#else
#error "Unknown Graphics backend for GLEEC!"
#endif

namespace GLEEC::Graphics
{
    struct Shader
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Shader shader = {};
#endif
    };
}
