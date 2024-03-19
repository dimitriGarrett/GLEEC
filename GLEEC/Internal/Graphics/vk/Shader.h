#pragma once

#include "Extensions.h"

#include <vector>

namespace GLEEC::Internal::Graphics::vk
{
    struct ShaderBinary
    {
        std::vector<char> code = {};

        // support caching in core and also loading from internal
        VkShaderCodeTypeEXT codeType = VK_SHADER_CODE_TYPE_SPIRV_EXT;

        std::string filepath = "";
    };

    // holds enough data to be able to create a shader
    struct PreparedShader
    {
        ShaderBinary binary = {};

        VkShaderCreateInfoEXT createInfo = {};
    };

    // create from prepared shaders
    struct Shader
    {
        VkShaderEXT shader = {};

        VkShaderCreateInfoEXT createInfo = {};

        ShaderBinary code = {};

        operator VkShaderEXT() const
        {
            return shader;
        }
    };

    GLEEC_API std::vector<PreparedShader> loadShaders(
        const std::vector<ShaderBinary>& shaders);

    GLEEC_API std::vector<PreparedShader> loadShaders(
        const std::vector<std::string>& shaders);

    GLEEC_API std::vector<Shader> createShaders(VkDevice device,
        const std::vector<PreparedShader>& preparedShaders,
        const std::vector<VkDescriptorSetLayout>& layouts,
        const std::vector<VkPushConstantRange>& pushConstants);

    GLEEC_API ShaderBinary readSPIRV(std::string_view filepath);

    inline ShaderBinary getShaderBinary(VkDevice device, VkShaderEXT shader)
    {
        ShaderBinary binary = {};

        size_t size = 0;
        vkGetShaderBinaryDataEXT(device, shader, &size, nullptr);

        binary.code.resize(size);

        vkGetShaderBinaryDataEXT(device, shader, &size, binary.code.data());

        return binary;
    }

    inline void destroyShader(VkDevice device, VkShaderEXT shader)
    {
        vkDestroyShaderEXT(device, shader, nullptr);
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
