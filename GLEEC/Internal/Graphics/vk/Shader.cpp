#include "Shader.h"

namespace GLEEC::Internal::Graphics::vk
{
    void createShaders(VkDevice device, std::vector<Shader>& shaders)
    {
        std::vector<VkShaderCreateInfoEXT> infos(shaders.size());
        std::vector<VkShaderEXT> vkShaders(shaders.size());

        for (size_t i = 0; i < shaders.size(); ++i)
        {
            infos[i] = shaders[i].createInfo;
            infos[i].pCode = shaders[i].code.code.data();

            vkShaders[i] = shaders[i];
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
}
