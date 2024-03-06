#pragma once

#include "Shader.h"

namespace GLEEC::Internal::Graphics::vk
{
    inline void cmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer,
        bool value)
    {
        vkCmdSetRasterizerDiscardEnable(commandBuffer, value);
    }

    inline void cmdEnableRasterizer(VkCommandBuffer commandBuffer)
    {
        cmdSetRasterizerDiscardEnable(commandBuffer, false);
    }

    inline void cmdDisableRasterizer(VkCommandBuffer commandBuffer)
    {
        cmdSetRasterizerDiscardEnable(commandBuffer, true);
    }

    inline void cmdSetRasterizationSamples(VkCommandBuffer commandBuffer,
        VkSampleCountFlagBits samples)
    {
        vkCmdSetRasterizationSamplesEXT(commandBuffer, samples);
    }

    inline void cmdSetViewportWithCount(VkCommandBuffer commandBuffer,
        const std::vector<VkViewport>& viewports)
    {
        vkCmdSetViewportWithCount(commandBuffer,
            static_cast<uint32_t>(viewports.size()), viewports.data());
    }

    inline void cmdSetViewport(VkCommandBuffer commandBuffer,
        const VkViewport& viewport)
    {
        vkCmdSetViewportWithCount(commandBuffer, 1, &viewport);
    }

    inline void cmdSetScissorWithCount(VkCommandBuffer commandBuffer,
        const std::vector<VkRect2D>& scissors)
    {
        vkCmdSetScissorWithCount(commandBuffer,
            static_cast<uint32_t>(scissors.size()), scissors.data());
    }

    inline void cmdSetScissor(VkCommandBuffer commandBuffer,
        const VkRect2D& scissor)
    {
        vkCmdSetScissorWithCount(commandBuffer, 1, &scissor);
    }

    inline void cmdSetLineWidth(VkCommandBuffer commandBuffer, float width)
    {
        vkCmdSetLineWidth(commandBuffer, width);
    }

    inline void cmdResetLineWidth(VkCommandBuffer commandBuffer)
    {
        cmdSetLineWidth(commandBuffer, 1.0f);
    }

    inline void cmdSetPolygonMode(VkCommandBuffer commandBuffer,
        VkPolygonMode polygonMode)
    {
        vkCmdSetPolygonModeEXT(commandBuffer, polygonMode);
    }

    inline void cmdSetColorBlendEnable(VkCommandBuffer commandBuffer,
        uint32_t firstAttachment, const std::vector<VkBool32>& enables)
    {
        vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment,
            static_cast<uint32_t>(enables.size()), enables.data());
    }

    inline void cmdSetColorBlendEnable(VkCommandBuffer commandBuffer,
        uint32_t firstAttachment, VkBool32 enable)
    {
        vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment,
            1, &enable);
    }

    inline void cmdSetColorBlendEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetColorBlendEnableEXT(commandBuffer, 0, 1, &enable);
    }

    inline void cmdSetColorBlendEquation(VkCommandBuffer commandBuffer,
        uint32_t firstAttachment,
        const std::vector<VkColorBlendEquationEXT>& equations)
    {
        vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment,
            static_cast<uint32_t>(equations.size()), equations.data());
    }

    inline void cmdSetColorBlendEquation(VkCommandBuffer commandBuffer,
        uint32_t firstAttachment, const VkColorBlendEquationEXT& equation)
    {
        vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, 1,
            &equation);
    }

    inline void cmdSetColorBlendEquation(VkCommandBuffer commandBuffer,
        const VkColorBlendEquationEXT& equation)
    {
        vkCmdSetColorBlendEquationEXT(commandBuffer, 0, 1, &equation);
    }

    inline void cmdSetPrimitiveTopology(VkCommandBuffer commandBuffer,
        VkPrimitiveTopology topology)
    {
        vkCmdSetPrimitiveTopology(commandBuffer, topology);
    }

    inline void cmdSetSampleMask(VkCommandBuffer commandBuffer,
        VkSampleCountFlagBits samples, VkSampleMask mask)
    {
        vkCmdSetSampleMaskEXT(commandBuffer, samples, &mask);
    }

    inline void cmdSetColorWriteMask(VkCommandBuffer commandBuffer,
        uint32_t firstAttachment,
        const std::vector<VkColorComponentFlags>& masks)
    {
        vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment,
            static_cast<uint32_t>(masks.size()), masks.data());
    }

    inline void cmdSetColorWriteMask(VkCommandBuffer commandBuffer,
        uint32_t firstAttachment,
        VkColorComponentFlags mask)
    {
        vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment,
            1, &mask);
    }

    inline void cmdSetColorWriteMask(VkCommandBuffer commandBuffer,
        VkColorComponentFlags mask)
    {
        vkCmdSetColorWriteMaskEXT(commandBuffer, 0, 1, &mask);
    }

    inline void cmdSetAlphaToCoverageEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, enable);
    }

    inline void cmdSetAlphaToOneEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetAlphaToOneEnableEXT(commandBuffer, enable);
    }

    inline void cmdSetCullMode(VkCommandBuffer commandBuffer,
        VkCullModeFlags cullMode)
    {
        vkCmdSetCullMode(commandBuffer, cullMode);
    }

    inline void cmdSetFrontFace(VkCommandBuffer commandBuffer,
        VkFrontFace frontFace)
    {
        vkCmdSetFrontFace(commandBuffer, frontFace);
    }

    inline void cmdSetDepthTestEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetDepthTestEnable(commandBuffer, enable);
    }

    inline void cmdSetDepthWriteEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetDepthWriteEnable(commandBuffer, enable);
    }

    inline void cmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetDepthBoundsTestEnable(commandBuffer, enable);
    }

    inline void cmdSetDepthBiasEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetDepthBiasEnable(commandBuffer, enable);
    }

    inline void cmdSetDepthClampEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetDepthClampEnableEXT(commandBuffer, enable);
    }

    inline void cmdSetStencilTestEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetStencilTestEnable(commandBuffer, enable);
    }

    inline void cmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetPrimitiveRestartEnable(commandBuffer, enable);
    }

    inline void cmdSetLogicOpEnable(VkCommandBuffer commandBuffer,
        VkBool32 enable)
    {
        vkCmdSetLogicOpEnableEXT(commandBuffer, enable);
    }

    template <size_t a, size_t b>
    inline void cmdSetVertexInput(VkCommandBuffer commandBuffer,
        const std::array<VkVertexInputBindingDescription2EXT, a>& bindings,
        const std::array<VkVertexInputAttributeDescription2EXT, b>& attributes)
    {
        vkCmdSetVertexInputEXT(commandBuffer,
            static_cast<uint32_t>(bindings.size()), bindings.data(),
            static_cast<uint32_t>(attributes.size()), attributes.data());
    }

    inline void cmdSetVertexInput(VkCommandBuffer commandBuffer,
        const std::vector<VkVertexInputBindingDescription2EXT>& bindings,
        const std::vector<VkVertexInputAttributeDescription2EXT>& attributes)
    {
        vkCmdSetVertexInputEXT(commandBuffer,
            static_cast<uint32_t>(bindings.size()), bindings.data(),
            static_cast<uint32_t>(attributes.size()), attributes.data());
    }
}
