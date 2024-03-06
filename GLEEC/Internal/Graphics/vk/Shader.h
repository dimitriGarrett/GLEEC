#pragma once

#include "Internal/Graphics/vk/PhysicalDevice.h"

#include "Internal/Config/Directory.h"

#include "Extensions.h"

#include <fstream>
#include <filesystem>

namespace GLEEC::Internal::Graphics::vk
{
    struct ShaderCacheHeader
    {
        size_t magic = 3175928559; // 0xDEAD_BEEF

        size_t size = 0;
    };

    struct ShaderCache
    {
        size_t size = 0;

        std::vector<char> code = {};
    };

    struct CreateShaderInfo
    {
        VkShaderCreateInfoEXT createInfo = {};
        ShaderCache code = {};
    };

    struct Shader
    {
        VkShaderEXT shader = {};

        VkShaderCreateInfoEXT createInfo = {};
        ShaderCache code = {};

        std::string name = "";
        std::string filepath = "";

        operator VkShaderEXT() const
        {
            return shader;
        }
    };

    GLEEC_API void createShaders(VkDevice device,
        std::vector<Shader>& shaders);

    GLEEC_API void createShader(VkDevice device, Shader& shader);

    inline ShaderCache readSPIRV(std::string_view filepath)
    {
        // just read the file and return it
        std::ifstream file(filepath.data(),
            std::ios::ate | std::ios::binary);

        ShaderCache cache = {};

        cache.size = static_cast<size_t>(file.tellg());
        cache.code = std::vector<char>(cache.size);

        file.seekg(0);
        file.read(cache.code.data(), cache.size);

        LOG_MESSAGE("Loaded SPIRV file: {} with code size: {}",
            filepath, cache.size);

        return cache;
    }

    // all of the complexity allows for identical names of shader files,
    // but in different directories. if only using name its impossible
    inline std::string getCachedShaderName(std::string_view filepath)
    {
        std::string full(filepath);
// why does windows have to be so difficult :(
#if GLEEC_WINDOWS
        for (char& c : full)
        {
            if (c == '\\') c = '/';
        }
#endif

        std::string path = full.substr(0, full.find_last_of('/'));
        std::string newstr = path.substr(0, path.find_last_of('/'));

        std::string end = full.substr(newstr.size() + 1, full.find_last_of('.') - newstr.size() - 1);
        end[end.find('/')] = '-';

        return end;
    }

    inline std::string cachedShaderFilepath(std::string_view name)
    {
        return Config::GLEECDirectory() + "gcache/GCVKSB-" + std::string(name) + ".bin";
    }

    inline bool cachedShaderExists(std::string_view name)
    {
        return std::filesystem::exists(cachedShaderFilepath(name));
    }

    inline Shader readShader(std::string_view filepath,
        VkShaderStageFlagBits stage, VkShaderStageFlags nextStage,
        VkShaderCreateFlagsEXT flags,
        uint32_t layoutCount, const VkDescriptorSetLayout* setLayouts,
        uint32_t rangeCount, const VkPushConstantRange* pushConstants,
        const VkSpecializationInfo* specializationInfo = nullptr)
    {
        if (!std::filesystem::exists(filepath))
        {
            LOG_WARNING("Attempted to create shader from filepath: {}, doesn't exist!",
                filepath);

            return {};
        }

        // i am gonna set myself up good for the future and require ONLY spirv shaders
        // thats because you dont want to compile at runtime, and its a postbuildstep
        // in premake so it should happen automatically anyways

        if (filepath.find("spv") == filepath.npos)
        {
            LOG_WARNING("Invalid shader file: {}, must be a SPIRV file!",
                filepath);

            return {};
        }

        ShaderCache loaded = readSPIRV(filepath);

        return {
            VK_NULL_HANDLE,

            {
                VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT,
                nullptr,
                flags,
                stage,
                nextStage,
                VK_SHADER_CODE_TYPE_SPIRV_EXT,
                loaded.size,
                nullptr,
                "main",
                layoutCount,
                setLayouts,
                rangeCount,
                pushConstants,
                specializationInfo
            },

            loaded,

            getCachedShaderName(filepath),
            std::string(filepath),
        };
    }

    inline Shader readShader(std::string_view filepath,
        VkShaderStageFlagBits stage, VkShaderStageFlags nextStage,
        VkShaderCreateFlagsEXT flags,
        const std::vector<VkDescriptorSetLayout>& setLayouts,
        const std::vector<VkPushConstantRange>& pushConstants,
        const VkSpecializationInfo* specializationInfo = nullptr)
    {
        return readShader(filepath, stage, nextStage, flags,
            static_cast<uint32_t>(setLayouts.size()), setLayouts.data(),
            static_cast<uint32_t>(pushConstants.size()), pushConstants.data(),
            specializationInfo);
    }

    inline Shader loadCachedShader(std::string_view filepath,
        VkShaderStageFlagBits stage, VkShaderStageFlags nextStage,
        VkShaderCreateFlagsEXT flags,
        const std::vector<VkDescriptorSetLayout>& setLayouts,
        const std::vector<VkPushConstantRange>& pushConstants,
        const VkSpecializationInfo* specializationInfo = nullptr)
    {
        std::string name = getCachedShaderName(filepath);

        if (!cachedShaderExists(name))
        {
            LOG_WARNING("Failed to load cached shader: {}, cache file: {} doesn't exist!",
                name, cachedShaderFilepath(name));

            return readShader(filepath, stage, nextStage, flags,
                setLayouts, pushConstants, specializationInfo);
        }

        std::ifstream file(cachedShaderFilepath(name),
            std::ios::in | std::ios::binary);

        ShaderCacheHeader header = {};

        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (header.magic != ShaderCacheHeader{}.magic)
        {
            LOG_WARNING("Invalid magic number: {} for shader {}: name (should be: {})",
                header.magic, name, ShaderCacheHeader{}.magic);

            return readShader(filepath, stage, nextStage, flags,
                setLayouts, pushConstants, specializationInfo);
        }

        ShaderCache cache = {};
        cache.size = header.size;

        //file.read(reinterpret_cast<char*>(&cache.size), sizeof(cache.size));

        if (cache.size == 0)
        {
            LOG_WARNING("Size of cached shader: {} was 0!", name);

            return readShader(filepath, stage, nextStage, flags,
                setLayouts, pushConstants, specializationInfo);
        }

        cache.code.resize(cache.size);

        file.read(cache.code.data(), cache.size);

        LOG_MESSAGE("Loaded cached shader file: {}, with size of: {}",
            cachedShaderFilepath(name), cache.size);

        return {
            VK_NULL_HANDLE,

            {
                VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT,
                nullptr,
                flags,
                stage,
                nextStage,
                VK_SHADER_CODE_TYPE_BINARY_EXT,
                cache.size,
                nullptr,
                "main",
                static_cast<uint32_t>(setLayouts.size()),
                setLayouts.data(),
                static_cast<uint32_t>(pushConstants.size()),
                pushConstants.data(),
                specializationInfo
            },

            cache,

            name,
            std::string(filepath),
        };
    }

    inline Shader loadShader(std::string_view filepath,
        VkShaderStageFlagBits stage, VkShaderStageFlags nextStage,
        VkShaderCreateFlagsEXT flags,
        const std::vector<VkDescriptorSetLayout>& setLayouts,
        const std::vector<VkPushConstantRange>& pushConstants,
        const VkSpecializationInfo* specializationInfo = nullptr)
    {
        if (cachedShaderExists(getCachedShaderName(filepath)))
        {
            return loadCachedShader(filepath,
                stage, nextStage, flags, setLayouts, pushConstants,
                specializationInfo);
        }

        return readShader(filepath, stage, nextStage, flags,
            setLayouts, pushConstants, specializationInfo);
    }

    inline void writeCachedShader(VkDevice device,
        std::string_view name, VkShaderEXT shader)
    {
        ShaderCacheHeader header = {};

        std::ofstream file(cachedShaderFilepath(name),
            std::ios::out | std::ios::binary);

        ShaderCache cache = {};

        vkGetShaderBinaryDataEXT(device, shader, &cache.size, nullptr);

        cache.code.resize(cache.size);

        vkGetShaderBinaryDataEXT(device, shader, &cache.size, cache.code.data());

        header.size = cache.size;

        file.write(reinterpret_cast<const char*>(&header), sizeof(header));
        //file.write(reinterpret_cast<const char*>(&cache.size), sizeof(cache.size));
        file.write(cache.code.data(), cache.size);

        LOG_MESSAGE("Wrote shader cache file: {} with size: {}",
            cachedShaderFilepath(name), header.size);
    }

    inline void writeCachedShader(VkDevice device, const Shader& shader)
    {
        writeCachedShader(device, shader.name, shader);
    }

    inline void destroyShader(VkDevice device, VkShaderEXT shader)
    {
        vkDestroyShaderEXT(device, shader, nullptr);
    }

    inline void destroyShader(VkDevice device, const Shader& shader)
    {
        writeCachedShader(device, shader);
        destroyShader(device, shader.shader);
    }

    inline void destroyShaders(VkDevice device,
        const std::vector<VkShaderEXT>& shaders)
    {
        for (const VkShaderEXT& shader : shaders)
        {
            destroyShader(device, shader);
        }
    }

    inline void destroyShaders(VkDevice device,
        const std::vector<Shader>& shaders)
    {
        for (size_t i = 0; i < shaders.size(); ++i)
        {
            writeCachedShader(device, shaders[i]);
            destroyShader(device, shaders[i].shader);
        }
    }

    inline void cmdBindShaders(VkCommandBuffer commandBuffer,
        uint32_t stageCount, const VkShaderStageFlagBits* stages,
        const VkShaderEXT* shaders)
    {
        vkCmdBindShadersEXT(commandBuffer, stageCount, stages, shaders);
    }

    inline void cmdBindShaders(VkCommandBuffer commandBuffer,
        const std::vector<Shader>& shaders)
    {
        std::vector<VkShaderStageFlagBits> stages(shaders.size());
        std::vector<VkShaderEXT> vkShaders(shaders.size());

        for (size_t i = 0; i < shaders.size(); ++i)
        {
            stages[i] = shaders[i].createInfo.stage;
            vkShaders[i] = shaders[i];
        }

        cmdBindShaders(commandBuffer,
            static_cast<uint32_t>(stages.size()), stages.data(), vkShaders.data());
    }

    inline void cmdBindShader(VkCommandBuffer commandBuffer,
        VkShaderStageFlagBits shaderStage, VkShaderEXT shader)
    {
        vkCmdBindShadersEXT(commandBuffer, 1, &shaderStage, &shader);
    }

    inline void cmdBindShader(VkCommandBuffer commandBuffer,
        const Shader& shader)
    {
        cmdBindShader(commandBuffer, shader.createInfo.stage, shader);
    }
}
