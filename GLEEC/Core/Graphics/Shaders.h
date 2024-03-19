#pragma once

#include "Shader.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DescriptorSetLayout.h"
#include "Internal/Graphics/vk/PipelineLayout.h"
#endif

namespace GLEEC::Graphics
{
#if GLEEC_GRAPHICS_BACKEND
    using DescriptorSetBindings = std::vector<
        Internal::Graphics::vk::DescriptorSetBinding>;
    using DescriptorSets = std::vector<DescriptorSetBindings>;
#endif

    struct Shaders
    {
        std::vector<Shader> shaders = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        std::vector<Internal::Graphics::vk::DescriptorSetLayout>
            descriptorSetLayouts = {};

        DescriptorSets bindings = {};

        Internal::Graphics::vk::PipelineLayout pipelineLayout = {};
#endif
    };
}
