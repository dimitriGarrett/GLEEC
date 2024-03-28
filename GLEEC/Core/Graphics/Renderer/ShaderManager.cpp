#include "ShaderManager.h"
#include "ShaderReflection.h"

#include "Core/Caching/Cache.h"
#include "Core/Caching/Specializations.h"

#include "Core/Config/Configuration.h"

#include <filesystem>

namespace GLEEC::Graphics
{
    std::unordered_map<size_t, Shaders> ShaderManager::shaders = {};

#define SHADER_CLASS(s) s.substr(s.find_last_of('/') + 1, 2)
#define SHADER_CLASS_INDEX(s) std::hash<std::string>{}(SHADER_CLASS(s))

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#define SHADER_LAYOUT_LOC(s) "shader-dslb-" + SHADER_CLASS(s)

    void ShaderManager::loadShadersBindings(Shaders& shaders,
        const std::vector<std::string>& grouped)
    {
        std::string shaderClass = SHADER_CLASS(grouped[0]);
        std::string layoutcache = SHADER_LAYOUT_LOC(std::string(shaderClass));

        if (Caching::getCachedResourceExists(Caching::DESCRIPTOR_SET_LAYOUT,
            layoutcache))
        {
            shaders.bindings = Caching::createPossiblyCachedResource
                <decltype(shaders.bindings)>(layoutcache);

            LOG_MESSAGE("Layout: {} loaded from cache!", layoutcache);
        }

        else
        {
            shaders.bindings = reflectShaders(Internal::Graphics::vk::loadShaders(
                grouped)).bindings;

            LOG_MESSAGE("Layout: {} reflected form shaders!", layoutcache);
        }
    }
#endif

    inline void ShaderManager::loadShaders(Shaders& shaders,
        const std::vector<std::string>& grouped)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        loadShadersBindings(shaders, grouped);
#endif

        for (const std::vector<Internal::Graphics::vk::DescriptorSetBinding>&
            bindings : shaders.bindings)
        {
            shaders.layouts.push_back(
                Internal::Graphics::vk::createDescriptorSetLayout(
                    GPUManager::activeGPU.device, bindings));
        }

        shaders.pipelineLayout = Internal::Graphics::vk::createPipelineLayout(
            GPUManager::activeGPU.device, shaders.layouts, {});
    }

    void ShaderManager::createShaders(Shaders& shaders,
        const std::vector<std::string>& grouped)
    {
        loadShaders(shaders, grouped);
            
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        std::vector<Internal::Graphics::vk::ShaderBinary> binaries = {};

        bool redo = false;
        if (Caching::getCachedResourceExists(Caching::SHADER,
            Caching::getCachedName(grouped[0])))
        {
            for (const std::string& shader : grouped)
            {
                binaries.push_back(Caching::createPossiblyCachedResource
                    <Internal::Graphics::vk::ShaderBinary>(shader));
                binaries.back().filepath = shader;
            }
        }

        else
        {
            redo = true;
            for (const std::string& shader : grouped)
            {
                binaries.push_back(Internal::Graphics::vk::readSPIRV(shader));
            }
        }

        std::vector<Internal::Graphics::vk::PreparedShader> prepared =
            Internal::Graphics::vk::loadShaders(binaries);

        std::vector<Internal::Graphics::vk::Shader> vkShaders =
            Internal::Graphics::vk::createShaders(
                GPUManager::activeGPU.device,
                prepared, shaders.layouts, {});

        // HUGE HACK: instead of figuring out why loading shaders only works
        // when using caching, just load the shaders as if they were cached.
        //
        // TODO: fix this and figure out why this wasn't working in the first place
        //
        // MAY REQUIRE a complete rewrite of the shader manager, complete
        // rewrites of the vk shader and caching have already been done to no avail.
        if (redo)
        {
            binaries.clear();

            int i = 0;
            for (const auto& shader : vkShaders)
            {
                binaries.push_back(Internal::Graphics::vk::getShaderBinary(
                    GPUManager::activeGPU.device, shader));

                binaries.back().codeType = VK_SHADER_CODE_TYPE_BINARY_EXT;
                binaries.back().filepath = prepared[i++].binary.filepath;
            }

            Internal::Graphics::vk::destroyShaders(
                GPUManager::activeGPU.device, vkShaders);

            prepared = Internal::Graphics::vk::loadShaders(binaries);

            vkShaders = Internal::Graphics::vk::createShaders(
                GPUManager::activeGPU.device, prepared,
                shaders.layouts, {});
        }

        for (const Internal::Graphics::vk::Shader& shader : vkShaders)
        {
            shaders.shaders.emplace_back(shader);
        }
#endif
    }

    void ShaderManager::init(
        const std::vector<std::vector<std::string>>& shaderGroups)
    {
        for (const std::vector<std::string>& group : shaderGroups)
        {
            std::string shaderClass = SHADER_CLASS(group[0]);

            Shaders& shaders = getShaders(shaderClass);
            shaders.shaderClass = SHADER_CLASS_INDEX(group[0]);

            createShaders(shaders, group);
        }
    }

    void ShaderManager::init(std::string_view directory)
    {
        std::unordered_map<size_t, std::vector<std::string>> shaderGroups = {};

        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            std::string path = entry.path().string();

            if (!path.ends_with("spv")) continue;

            shaderGroups[SHADER_CLASS_INDEX(path)].push_back(path);
        }

        std::vector<std::vector<std::string>> shaders = {};

        for (const auto& [_, group] : shaderGroups)
        {
            shaders.push_back(group);
        }

        init(shaders);
    }

    inline void ShaderManager::init()
    {
        init(Config::Configuration::gets("shaders_dir"));
    }

    void ShaderManager::destroyShaders(Shaders& shaders)
    {
        for (const Shader& shader : shaders.shaders)
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Caching::cacheResource(shader.shader.code.filepath,
                Internal::Graphics::vk::getShaderBinary(
                    GPUManager::activeGPU.device, shader.shader));

            Internal::Graphics::vk::destroyShader(
                GPUManager::activeGPU.device, shader.shader);
#endif
        }
    }

    inline void ShaderManager::destroy()
    {
        for (auto& [_, group] : shaders)
        {
            destroyShaders(group);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Caching::cacheResource(
                SHADER_LAYOUT_LOC(group.shaders[0].shader.code.filepath),
                group.bindings);

            for (const Internal::Graphics::vk::DescriptorSetLayout& layout :
                group.layouts)
            {
                Internal::Graphics::vk::destroyDescriptorSetLayout(
                    GPUManager::activeGPU.device, layout);
            }

            Internal::Graphics::vk::destroyPipelineLayout(
                GPUManager::activeGPU.device, group.pipelineLayout);
#endif
        }
    }

    inline void ShaderManager::bindShaders(const FrameData& frame,
        size_t shaderClass)
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
