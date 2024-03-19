#pragma once

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DescriptorSetLayout.h"
#endif

namespace GLEEC::Graphics
{
    struct RenderState
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        bool enableRendering = true;

        float lineWidth = 1.0f;

        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;

        VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
        VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT;
        VkFrontFace frontFace = VK_FRONT_FACE_CLOCKWISE;

        VkColorBlendEquationEXT blendEquation = {
            VK_BLEND_FACTOR_ONE,
            VK_BLEND_FACTOR_ZERO,
            VK_BLEND_OP_ADD,
            VK_BLEND_FACTOR_ONE,
            VK_BLEND_FACTOR_ZERO,
            VK_BLEND_OP_ADD,
        };

        VkSampleMask sampleMask = 0xFF;
        VkColorComponentFlags colorWriteMask = 0xF;
#endif
    };
}
