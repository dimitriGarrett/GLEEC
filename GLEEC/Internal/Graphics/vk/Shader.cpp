#include "Shader.h"

namespace GLEEC::Internal::Graphics::vk
{
    void createShaders(VkDevice device, std::vector<Shader>& shaders)
    {
        std::vector<VkShaderCreateInfoEXT> infos(shaders.size());
        std::vector<VkShaderEXT> vkShaders(shaders.size());

        // if the shader cache and the shader spv differ, load spv
        // BUT: vulkan requires that all linked shaders are created in the same way
        // so that means if one differs, have to disregard ALL caches
        // this is so annoying :(

        // this is mainly for debugging and writing shaders,
        // in release and prod code they should always be the same
#if GLEEC_DEBUG
        for (Shader& shader : shaders)
        {
            if (shader.loadedFromCache && !verifyCache(device, shader))
            {

                LOG_MESSAGE("Shader cache: {} differs from shader file: {}, disregarding caching, loading all files from spv!",
                    cachedShaderFilepath(shader.name), shader.filepath);

                for (Shader& toReload : shaders)
                {
                    toReload = readShader(
                        toReload.filepath,
                        toReload.createInfo.stage,
                        toReload.createInfo.nextStage,
                        toReload.createInfo.flags,
                        toReload.createInfo.setLayoutCount,
                        toReload.createInfo.pSetLayouts,
                        toReload.createInfo.pushConstantRangeCount,
                        toReload.createInfo.pPushConstantRanges,
                        toReload.createInfo.pSpecializationInfo);
                }

                break;
            }
        }
#endif

        for (size_t i = 0; i < shaders.size(); ++i)
        {
            Shader& shader = shaders[i];

            infos[i] = shader.createInfo;
            infos[i].pCode = shader.code.code.data();

            vkShaders[i] = shader;
        }

        VkResult res = vkCreateShadersEXT(device,
            static_cast<uint32_t>(shaders.size()),
            infos.data(), nullptr, vkShaders.data());

        if (res == VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT)
        {
            LOG_WARNING("Incompatible shader binaries! (failed loading cached shaders, falling back on actual files!!)");

            std::vector<Shader> newShaders(shaders.size());
            for (size_t i = 0; i < shaders.size(); ++i)
            {
                VkShaderEXT shader = vkShaders[i];
                Shader& actualShader = shaders[i];

                if (shader == VK_NULL_HANDLE)
                {
                    LOG_MESSAGE("Shader cache file: {} was corrupted!",
                        actualShader.name);

                    newShaders[i] = readShader(
                        actualShader.filepath,
                        actualShader.createInfo.stage,
                        actualShader.createInfo.nextStage,
                        actualShader.createInfo.flags,
                        actualShader.createInfo.setLayoutCount,
                        actualShader.createInfo.pSetLayouts,
                        actualShader.createInfo.pushConstantRangeCount,
                        actualShader.createInfo.pPushConstantRanges,
                        actualShader.createInfo.pSpecializationInfo);
                }

                else
                {
                    newShaders[i] = shaders[i];
                }

                Shader& newShader = newShaders[i];

                infos[i] = newShader.createInfo;
                infos[i].pCode = newShader.code.code.data();
            }

            vkCreateShadersEXT(device, static_cast<uint32_t>(shaders.size()),
                infos.data(), nullptr, vkShaders.data());

            LOG_MESSAGE("Reloaded shaders from failed cached files!");
        }

        for (size_t i = 0; i < shaders.size(); ++i)
        {
            shaders[i].shader = vkShaders[i];
        }
    }

    void createShader(VkDevice device, Shader& shader)
    {
#if GLEEC_DEBUG
        // shader cache and file differ, load the file instead
        if (shader.loadedFromCache && !verifyCache(device, shader))
        {
            shader = readShader(
                shader.filepath,
                shader.createInfo.stage,
                shader.createInfo.nextStage,
                shader.createInfo.flags,
                shader.createInfo.setLayoutCount,
                shader.createInfo.pSetLayouts,
                shader.createInfo.pushConstantRangeCount,
                shader.createInfo.pPushConstantRanges,
                shader.createInfo.pSpecializationInfo);

            LOG_MESSAGE("Shader cache: {} differs from shader file: {}, loading file instead!",
                cachedShaderFilepath(shader.name), shader.filepath);
        }
#endif

        shader.createInfo.pCode = shader.code.code.data();
        VkResult res = vkCreateShadersEXT(device, 1, &shader.createInfo,
            nullptr, &shader.shader);

        if (res == VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT)
        {
            LOG_WARNING("Incompatible shader binaries! (failed loading cached shaders, falling back on actual files!!)");

            if (shader != VK_NULL_HANDLE)
            {
                destroyShader(device, shader);
            }

            else
            {
                LOG_MESSAGE("Shader cache file: {} was corrupted!",
                    shader.name);
            }

            Shader newShader = readShader(
                shader.filepath,
                shader.createInfo.stage,
                shader.createInfo.nextStage,
                shader.createInfo.flags,
                shader.createInfo.setLayoutCount,
                shader.createInfo.pSetLayouts,
                shader.createInfo.pushConstantRangeCount,
                shader.createInfo.pPushConstantRanges,
                shader.createInfo.pSpecializationInfo);

            shader.createInfo = newShader.createInfo;
            shader.createInfo.pCode = newShader.code.code.data();

            vkCreateShadersEXT(device, 1, &shader.createInfo,
                nullptr, &shader.shader);

            LOG_MESSAGE("Reloaded shaders from failed cached files!");
        }
    }

    bool verifyCache(VkDevice device, const Shader& shader)
    {
        // cant link a shader of only one stage
        constexpr uint32_t removeLink = ~(VK_SHADER_CREATE_LINK_STAGE_BIT_EXT);

        Shader noncached = readShader(shader.filepath,
            shader.createInfo.stage,
            shader.createInfo.nextStage,
            shader.createInfo.flags & removeLink,
            shader.createInfo.setLayoutCount,
            shader.createInfo.pSetLayouts,
            shader.createInfo.pushConstantRangeCount,
            shader.createInfo.pPushConstantRanges,
            shader.createInfo.pSpecializationInfo);

        createShader(device, noncached);

        bool val = getShaderBinary(device, noncached) == shader.code;

        destroyShader(device, noncached.shader);

        return val;
    }
}
