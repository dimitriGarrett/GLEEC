#include "RenderStateManager.h"

#include "Core/Graphics/Renderer/Model/VertexManager.h"
#include "Core/Window/WindowManager.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DynamicShaderState.h"
#endif

namespace GLEEC::Graphics
{
    std::vector<RenderState> RenderStateManager::renderStatePresets = { {} };
    size_t RenderStateManager::activeRenderState = 0;

    void RenderStateManager::prepareState(FrameData& frame, size_t i,
        RenderState& state)
    {
        Window::Window& window = Window::WindowManager::windows[i];

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        VkCommandBuffer commandBuffer = frame.commandBuffer;
        
        if (window.minimized)
        {
            Internal::Graphics::vk::cmdSetRasterizerDiscardEnable(commandBuffer,
                true);

            return;
        }

        Internal::Graphics::vk::cmdSetRasterizerDiscardEnable(commandBuffer,
            !state.enableRendering);

        VkViewport viewport = {};
        viewport.width = static_cast<float>(window.size().x);
        viewport.height = static_cast<float>(window.size().y);

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
