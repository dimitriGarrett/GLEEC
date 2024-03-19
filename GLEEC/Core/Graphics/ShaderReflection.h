#pragma once

#include "Shaders.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Shader.h"
#endif

namespace GLEEC::Graphics
{
    struct ReflectedShader
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        DescriptorSets bindings = {};
#endif
    };

    GLEEC_API_EXTERN ReflectedShader reflectShaders(
        const std::vector<Internal::Graphics::vk::PreparedShader>& shaders);
}
