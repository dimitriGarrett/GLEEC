#include "Shader.h"

#include <fstream>

namespace GLEEC::Internal::Graphics::vk
{
    inline VkShaderStageFlagBits stage(std::string_view filepath)
    {
        if (filepath.find("vert") != filepath.npos)
        {
            return VK_SHADER_STAGE_VERTEX_BIT;
        }

        else if (filepath.find("frag") != filepath.npos)
        {
            return VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        LOG_ERROR("Don't know how to read shader file: {}, name must contain the type of shader (vert, frag, etc)", filepath);

        return VK_SHADER_STAGE_ALL;
    }

    inline VkShaderStageFlags nextStage(std::string_view filepath)
    {
        if (filepath.find("vert") != filepath.npos)
        {
            return VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        else if (filepath.find("frag") != filepath.npos)
        {
            return 0;
        }

        LOG_ERROR("Don't know how to read shader file: {}, name must contain the type of shader (vert, frag, etc)", filepath);

        return -1;
    }

    std::vector<PreparedShader> loadShaders(const
        std::vector<ShaderBinary>& shaders)
    {
        std::vector<PreparedShader> prepared = {};

        for (const ShaderBinary& shader : shaders)
        {
            prepared.emplace_back(shader);

            prepared.back().createInfo = {
                VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT,
                nullptr,
                VK_SHADER_CREATE_LINK_STAGE_BIT_EXT,
                stage(shader.filepath),
                nextStage(shader.filepath),
                shader.codeType,
                static_cast<uint32_t>(shader.code.size()),
                nullptr,
                "main",
            };
        }

        return prepared;
    }

    ShaderBinary readSPIRV(std::string_view filepath)
    {
        ShaderBinary shader = {};

        std::ifstream file(filepath.data(),
            std::ios::in | std::ios::binary);

        file.seekg(0, std::ios_base::end);
        shader.code = std::vector<char>(file.tellg());

        file.seekg(0);
        file.read(shader.code.data(), shader.code.size());

        shader.codeType = VK_SHADER_CODE_TYPE_SPIRV_EXT;
        shader.filepath = filepath;

        return shader;
    }

    std::vector<Shader> createShaders(VkDevice device,
        const std::vector<PreparedShader>& preparedShaders,
        const std::vector<VkDescriptorSetLayout>& layouts,
        const std::vector<VkPushConstantRange>& pushConstants)
    {
        std::vector<VkShaderCreateInfoEXT> createInfos = {};
        std::vector<VkShaderEXT> shaders = {};

        for (const PreparedShader& shader : preparedShaders)
        {
            createInfos.push_back(shader.createInfo);

            createInfos.back().setLayoutCount =
                static_cast<uint32_t>(layouts.size());
            createInfos.back().pSetLayouts = layouts.data();

            createInfos.back().pushConstantRangeCount =
                static_cast<uint32_t>(pushConstants.size());
            createInfos.back().pPushConstantRanges = pushConstants.data();
            
            createInfos.back().pCode = shader.binary.code.data();

            shaders.emplace_back();
        }

        VkResult res = vkCreateShadersEXT(device,
            static_cast<uint32_t>(createInfos.size()),
            createInfos.data(), nullptr, shaders.data());

        // most likely from a corrupted cache,
        // at least assume that
        if (res == VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT)
        {
#if GLEEC_DEBUG
            for (size_t i = 0; i < shaders.size(); ++i)
            {
                if (shaders[i] == VK_NULL_HANDLE)
                    LOG_WARNING("Cache was corrupted for shader: {}",
                        preparedShaders[i].binary.filepath);
            }
#endif

            std::vector<ShaderBinary> preparedAgain = {};

            // must all be the same type (spirv)
            for (const PreparedShader& prepared : preparedShaders)
            {
                if (prepared.binary.codeType ==
                    VK_SHADER_CODE_TYPE_BINARY_EXT)
                {
                    preparedAgain.emplace_back(readSPIRV(prepared.binary.filepath));
                }

                else
                {
                    preparedAgain.emplace_back(prepared.binary);
                }
            }

            return createShaders(device, loadShaders(preparedAgain),
                layouts, pushConstants);
        }

        std::vector<Shader> tempShaders(shaders.size());

        for (size_t i = 0; i < tempShaders.size(); ++i)
        {
            tempShaders[i].shader = shaders[i];

            tempShaders[i].createInfo = preparedShaders[i].createInfo;
            tempShaders[i].code = preparedShaders[i].binary;
        }

        return tempShaders;
    }

    std::vector<PreparedShader> loadShaders(
        const std::vector<std::string>& shaders)
    {
        std::vector<ShaderBinary> shaderBinaries = {};

        for (const std::string& filepath : shaders)
        {
            shaderBinaries.emplace_back(readSPIRV(filepath));
        }

        return loadShaders(shaderBinaries);
    }
}
