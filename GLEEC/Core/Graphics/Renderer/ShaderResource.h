#pragma once

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DescriptorBuffer.h"
#endif

#include <unordered_map>

namespace GLEEC::Graphics
{
    struct ShaderResource
    {
        size_t index = {};

        size_t shaderClass = -1;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        uint32_t set = {};

        Internal::Graphics::vk::DescriptorBuffer descriptorBuffer = {};

        std::unordered_map<const void*, size_t> offsets = {};
#endif
    };
}
