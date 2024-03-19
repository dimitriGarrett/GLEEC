#include "ShaderReflection.h"

#include "reflect_spirv/spirv_reflect.h"

namespace GLEEC::Graphics
{
    DescriptorSets reflectDescriptorSets(
        const std::vector<Internal::Graphics::vk::PreparedShader>& shaders)
    {
        DescriptorSets bindings(4);

        for (const auto& shader : shaders)
        {
            SpvReflectShaderModule module = {};
            SpvReflectResult result =
                spvReflectCreateShaderModule(shader.binary.code.size(),
                    shader.binary.code.data(), &module);
            assert(result == SPV_REFLECT_RESULT_SUCCESS);

            uint32_t count = 0;

            result = spvReflectEnumerateDescriptorSets(&module,
                &count, nullptr);
            assert(result == SPV_REFLECT_RESULT_SUCCESS);

            std::vector<SpvReflectDescriptorSet*> descriptorSets(count);

            result = spvReflectEnumerateDescriptorSets(&module, &count,
                descriptorSets.data());
            assert(result == SPV_REFLECT_RESULT_SUCCESS);

            for (const SpvReflectDescriptorSet* set : descriptorSets)
            {
                for (size_t i = 0; i < set->binding_count; ++i)
                {
                    SpvReflectDescriptorBinding* binding =
                        set->bindings[i];

                    bindings[set->set].emplace_back(
                        binding->binding,
                        static_cast<VkDescriptorType>(binding->descriptor_type),
                        binding->count,
                        shader.createInfo.stage,
                        nullptr
                    );
                }
            }
        }

        DescriptorSets newBindings = {};

        for (const auto& binding : bindings)
        {
            if (binding.empty())
            {
                break;
            }

            newBindings.push_back(binding);
        }

        return newBindings;
    }

    ReflectedShader reflectShaders(
        const std::vector<Internal::Graphics::vk::PreparedShader>& shaders)
    {
        ReflectedShader reflected =

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        { reflectDescriptorSets(shaders) };
#else
        {};
#endif

        return reflected;
    }
}
