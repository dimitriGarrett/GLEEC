#include "ShaderManager.h"
#include "Core/Graphics/Renderer/Model/VertexManager.h"
#include "Core/Window/WindowManager.h"
#include "GPUManager.h"

#include "Core/Config/Configuration.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DynamicShaderState.h"
#endif

namespace GLEEC::Graphics
{
    std::unordered_map<size_t, Shader> ShaderManager::shaders = {};

    ShaderManagerState ShaderManager::state = {};

    Shader& ShaderManager::loadShader(std::string_view filepath)
    {
        if (shaders.contains(key(filepath)))
        {
            return shaders.at(key(filepath));
        }

        Shader& shader = shaders[key(filepath)];
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        shader.shader = Internal::Graphics::vk::loadShader(filepath,
            static_cast<VkShaderStageFlagBits>(
                getShaderTypeFromFilepath(filepath)),
            getNextShaderTypeFromFilepath(filepath),
            0, {}, {});
#endif
        return shader;
    }

    void ShaderManager::destroyShader(Shader& shader)
    {
#if GLEEC_GRAPHICS_BACKEND
        Internal::Graphics::vk::destroyShader(
            GPUManager::activeGPU.device, shader.shader);
#endif
    }

    uint32_t ShaderManager::getShaderTypeFromFilepath(std::string_view filepath)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        if (filepath.find("vert") != filepath.npos)
        {
            return VK_SHADER_STAGE_VERTEX_BIT;
        }

        else if (filepath.find("frag") != filepath.npos)
        {
            return VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        LOG_ERROR("Don't know how to read shader file: {}, name must contain the type of shader (vert, frag, etc)", filepath);

        return -1;
#endif
    }

    uint32_t ShaderManager::getNextShaderTypeFromFilepath(std::string_view filepath)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
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
#endif
    }

    inline void ShaderManager::init(const std::vector<std::vector<std::string>>& filepaths)
    {
        std::string shaderdir = Config::Configuration::gets("cwd")
            + "shaders/";

        for (const auto& linked : filepaths)
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            std::vector<Internal::Graphics::vk::Shader> temp = {};
#endif

            for (const std::string& first_filepath : linked)
            {
                std::string filepath = shaderdir + first_filepath;

                loadShader(filepath);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
                shaders[key(filepath)].shader.createInfo.flags |=
                    VK_SHADER_CREATE_LINK_STAGE_BIT_EXT;
#endif

                temp.push_back(shaders[key(filepath)].shader);
            }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::createShaders(
                GPUManager::activeGPU.device,
                temp);

            for (const auto& shader : temp)
            {
                shaders[key(shader.filepath)].shader = shader;
            }
#endif
        }
    }

    inline void ShaderManager::destroy()
    {
        for (auto& [_, shader] : shaders)
        {
            destroyShader(shader);
        }
    }

    inline void ShaderManager::bind(FrameData& frame, size_t i)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        // bind shaders
        {
            // need to bind null shader to unused shaders
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

            for (auto& [_, shader] : ShaderManager::shaders)
            {
                Internal::Graphics::vk::cmdBindShaders(frame.commandBuffer,
                    1, &shader.shader.createInfo.stage, &shader.shader.shader);
            }
        }
#endif
    }

    inline void ShaderManager::setState(FrameData& frame, size_t i)
    {
        Window::Window& window = Window::WindowManager::windows[i];

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkCommandBuffer commandBuffer = frame.commandBuffer;
        
        Internal::Graphics::vk::cmdSetRasterizerDiscardEnable(commandBuffer,
            !state.enableRendering);

        VkViewport viewport = {};
        viewport.width = static_cast<float>(window.size().x),
        viewport.height = static_cast<float>(window.size().y),

        Internal::Graphics::vk::cmdSetViewport(commandBuffer, viewport);

        VkRect2D scissor = {};
        scissor.extent.width = window.size().x;
        scissor.extent.height = window.size().y;

        Internal::Graphics::vk::cmdSetScissor(commandBuffer, scissor);

        Internal::Graphics::vk::cmdSetLineWidth(commandBuffer, state.lineWidth);

        Internal::Graphics::vk::cmdSetPolygonMode(commandBuffer,
            state.polygonMode);
        Internal::Graphics::vk::cmdSetPrimitiveTopology(commandBuffer,
            state.topology);

        Internal::Graphics::vk::cmdSetColorBlendEnable(commandBuffer, 1);
        Internal::Graphics::vk::cmdSetColorBlendEquation(commandBuffer, state.blendEquation);

        Internal::Graphics::vk::cmdSetRasterizationSamples(commandBuffer,
            state.samples);

        Internal::Graphics::vk::cmdSetSampleMask(commandBuffer,
            state.samples, state.sampleMask);
        Internal::Graphics::vk::cmdSetColorWriteMask(commandBuffer,
            state.colorWriteMask);

        Internal::Graphics::vk::cmdSetAlphaToCoverageEnable(commandBuffer, 0);
        Internal::Graphics::vk::cmdSetAlphaToOneEnable(commandBuffer, 0);

        Internal::Graphics::vk::cmdSetCullMode(commandBuffer,
            state.cullMode);
        Internal::Graphics::vk::cmdSetFrontFace(commandBuffer,
            state.frontFace);

        Internal::Graphics::vk::cmdSetDepthTestEnable(commandBuffer,
            VK_FALSE);
        Internal::Graphics::vk::cmdSetDepthWriteEnable(commandBuffer,
            VK_FALSE);
        Internal::Graphics::vk::cmdSetDepthBoundsTestEnable(commandBuffer,
            VK_FALSE);
        Internal::Graphics::vk::cmdSetDepthBiasEnable(commandBuffer,
            VK_FALSE);
        Internal::Graphics::vk::cmdSetStencilTestEnable(commandBuffer,
            VK_FALSE);

        Internal::Graphics::vk::cmdSetDepthClampEnable(commandBuffer,
            VK_FALSE);

        Internal::Graphics::vk::cmdSetPrimitiveRestartEnable(commandBuffer,
            VK_FALSE);

        Internal::Graphics::vk::cmdSetLogicOpEnable(commandBuffer,
            VK_FALSE);

        Internal::Graphics::vk::cmdSetVertexInput(commandBuffer,
            VertexManager::bindingDescription(),
            VertexManager::attributeDescription());
#endif
    }
}
