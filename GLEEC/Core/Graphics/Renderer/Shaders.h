#pragma once

#include "Shader.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DescriptorSetLayout.h"
#include "Internal/Graphics/vk/PipelineLayout.h"
#endif

namespace GLEEC::Graphics
{
    struct Shaders
    {
        std::vector<Shader> shaders = {};
        size_t shaderClass = -1;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        std::vector<Internal::Graphics::vk::DescriptorSetLayout>
            layouts = {};
        std::vector<std::vector<Internal::Graphics::vk::DescriptorSetBinding>>
            bindings = {};

        Internal::Graphics::vk::PipelineLayout pipelineLayout = {};
#endif
    };
}
