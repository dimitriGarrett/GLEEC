#include "ShaderManager.h"
#include "ShaderReflection.h"

#include "Core/Caching/Specializations.h"

namespace GLEEC::Graphics
{
    std::unordered_map<size_t, Shaders> ShaderManager::shaders = {};

#define SHADER_CLASS(group)\
    group.substr(group.find_last_of('/') + 1, 2)
#define SHADER_DSLB(group) "shader-dslb-" + SHADER_CLASS(group)

    void ShaderManager::init(const std::vector<std::vector<std::string>>&
        shaderGroups)
    {
        for (const std::vector<std::string>& shaderGroup : shaderGroups)
        {
            std::string shaderClass = SHADER_CLASS(shaderGroup[0]);

            Shaders& grouped = getShaders(shaderClass);

            // descriptor set bindings cache
            std::string cached = SHADER_DSLB(shaderGroup[0]);
            if (Caching::getCachedResourceExists(Caching::DESCRIPTOR_SET_LAYOUT,
                cached))
            {
                grouped.bindings = Caching::createPossiblyCachedResource
                    <decltype(grouped.bindings)>(cached);

                LOG_MESSAGE("Descriptor set layout: {} loaded from cache!",
                    cached);
            }

            else
            {
                grouped.bindings = reflectShaders(
                    Internal::Graphics::vk::loadShaders(shaderGroup)).bindings;

                LOG_MESSAGE("Descriptor set layout: {} reflected from: {}!",
                    cached, shaderClass);
            }
            
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            for (const Internal::Graphics::vk::DescriptorSetBindings& bindings :
                grouped.bindings)
            {
                grouped.descriptorSetLayouts.push_back(
                    Internal::Graphics::vk::createDescriptorSetLayout(
                        GPUManager::activeGPU.device, bindings));
            }

            grouped.pipelineLayout =
                Internal::Graphics::vk::createPipelineLayout(
                    GPUManager::activeGPU.device,
                    grouped.descriptorSetLayouts, {});

            std::vector<Internal::Graphics::vk::ShaderBinary> binary = {};

            bool redo = false;
            if (Caching::getCachedResourceExists(Caching::SHADER,
                Caching::getCachedName(shaderGroup[0])))
            {
                for (const std::string& shader : shaderGroup)
                {
                    binary.push_back(Caching::createPossiblyCachedResource
                        <Internal::Graphics::vk::ShaderBinary>(shader));
                    binary.back().filepath = shader;
                }
            }

            else
            {
                redo = true;
                for (const std::string& shader : shaderGroup)
                {
                    binary.push_back(Internal::Graphics::vk::readSPIRV(shader));
                }
            }

            std::vector<Internal::Graphics::vk::PreparedShader> prepared =
                Internal::Graphics::vk::loadShaders(binary);

            std::vector<Internal::Graphics::vk::Shader> vkShaders =
                Internal::Graphics::vk::createShaders(
                    GPUManager::activeGPU.device,
                    prepared, grouped.descriptorSetLayouts, {});

            // HUGE HACK: instead of figuring out why loading shaders only works
            // when using caching, just load the shaders as if they were cached.
            //
            // TODO: fix this and figure out why this wasn't working in the first place
            //
            // MAY REQUIRE a complete rewrite of the shader manager, complete
            // rewrites of the vk shader and caching have already been done to no avail.
            if (redo)
            {
                binary.clear();

                int i = 0;
                for (const auto& shader : vkShaders)
                {
                    binary.push_back(Internal::Graphics::vk::getShaderBinary(
                        GPUManager::activeGPU.device, shader));

                    binary.back().codeType = VK_SHADER_CODE_TYPE_BINARY_EXT;
                    binary.back().filepath = prepared[i++].binary.filepath;
                }

                Internal::Graphics::vk::destroyShaders(
                    GPUManager::activeGPU.device, vkShaders);

                prepared = Internal::Graphics::vk::loadShaders(binary);

                vkShaders = Internal::Graphics::vk::createShaders(
                    GPUManager::activeGPU.device, prepared,
                    grouped.descriptorSetLayouts, {});
            }

            for (const Internal::Graphics::vk::Shader& shader : vkShaders)
            {
                grouped.shaders.emplace_back(shader);
            }
#endif
        }
    }

    void ShaderManager::init(std::string_view directory)
    {
        // iterate through directory and get all shaders present
        std::vector<std::vector<std::string>> shaders = {};
        std::unordered_map<size_t, size_t> shaderTypes = {};

        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            std::string path = entry.path().string();

            if (!path.ends_with("spv"))
            {
                LOG_MESSAGE("Skipped file: {} when iterating shader directory: {}!",
                    path, directory);

                continue;
            }

            size_t shaderClass = std::hash<std::string>{}(SHADER_CLASS(path));
            size_t offset = 0;

            if (shaderTypes.contains(shaderClass))
            {
                offset = shaderTypes.at(shaderClass);
            }

            else
            {
                offset = (shaderTypes[shaderClass] = shaderTypes.size());
                shaders.emplace_back();
            }

            shaders[offset].push_back(path);
        }

        return init(shaders);
    }

    inline void ShaderManager::init()
    {
        return init(Config::Configuration::gets("shaders_dir"));
    }

    void ShaderManager::destroy()
    {
        for (auto& [_, shaderGroup] : shaders)
        {
            for (const Shader& shader : shaderGroup.shaders)
            {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
                Caching::cacheResource(shader.shader.code.filepath,
                    Internal::Graphics::vk::getShaderBinary(
                        GPUManager::activeGPU.device, shader.shader));

                Internal::Graphics::vk::destroyShader(
                    GPUManager::activeGPU.device, shader.shader);
#endif
            }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Caching::cacheResource(
                SHADER_DSLB(shaderGroup.shaders[0].shader.code.filepath),
                shaderGroup.bindings);

            for (const Internal::Graphics::vk::DescriptorSetLayout& layout :
                shaderGroup.descriptorSetLayouts)
            {
                Internal::Graphics::vk::destroyDescriptorSetLayout(
                    GPUManager::activeGPU.device, layout);
            }

            Internal::Graphics::vk::destroyPipelineLayout(
                GPUManager::activeGPU.device, shaderGroup.pipelineLayout);
#endif
        }
    }

    void ShaderManager::bindShaders(const FrameData& frame, size_t shaderClass)
    {
        Shaders& shaderShaders = shaders[shaderClass];

        VkShaderStageFlagBits unused[] = {
            VK_SHADER_STAGE_VERTEX_BIT,
            VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
            VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
            VK_SHADER_STAGE_GEOMETRY_BIT,
            VK_SHADER_STAGE_FRAGMENT_BIT,
            VK_SHADER_STAGE_COMPUTE_BIT,
        };

        Internal::Graphics::vk::cmdBindShaders(frame.commandBuffer,
            sizeof(unused) / sizeof(unused[0]), unused, nullptr);

        for (const Shader& shader : shaderShaders.shaders)
        {
            Internal::Graphics::vk::cmdBindShaders(frame.commandBuffer,
                1, &shader.shader.createInfo.stage, &shader.shader.shader);
        }
    }
}
