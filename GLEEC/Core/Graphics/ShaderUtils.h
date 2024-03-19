#pragma once

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Shader.h"
#endif

namespace GLEEC::Graphics
{
    struct ShaderUtils
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static std::string shaderClass(std::string_view filepath);
        GLEEC_API static size_t shaderClassIndex(std::string_view filepath);

        GLEEC_API static std::string dslbFilepath(std::string_view shaderClass);
#endif
    };
}
