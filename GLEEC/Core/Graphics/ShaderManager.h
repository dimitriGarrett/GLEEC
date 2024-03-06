#pragma once

#include "Shader.h"
#include "Frame.h"

#include "Internal/Graphics/Backend.h"

#include <unordered_map>

namespace GLEEC::Graphics
{
    using Shaders = std::vector<Shader>;

    struct ShaderManagerState
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

    struct ShaderManager
    {
        GLEEC_API static void init(const std::vector<std::vector<std::string>>& shaders);
        GLEEC_API static void destroy();

        GLEEC_API static void bind(FrameData& frame, size_t index);
        GLEEC_API static void setState(FrameData& frame, size_t index);

        GLEEC_API static std::unordered_map<size_t, Shader> shaders;

        GLEEC_API static ShaderManagerState state;
    private:
        GLEEC_API static Shader& loadShader(std::string_view filepath);
        GLEEC_API static void destroyShader(Shader& shader);

        GLEEC_API static uint32_t getShaderTypeFromFilepath(std::string_view filepath);
        GLEEC_API static uint32_t getNextShaderTypeFromFilepath(std::string_view filepath);

        inline static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
