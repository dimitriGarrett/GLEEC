#pragma once

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Buffer.h"
#endif

namespace GLEEC::Graphics
{
    struct Buffer
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Buffer buffer = {};
#endif
    };
}
