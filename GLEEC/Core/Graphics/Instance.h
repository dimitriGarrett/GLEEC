#pragma once

#include "Internal/Graphics/Backend.h"
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Instance.h"
#else
#error "Unknown Graphics backend for GLEEC!"
#endif

namespace GLEEC::Graphics
{
    // just the instance for whatever internal graphics API is used
    // mainly for vulkan but who knows
    struct Instance
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Instance instance = {};
#endif
    };
}
