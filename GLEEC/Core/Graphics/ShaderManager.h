#pragma once

#include "Shaders.h"
#include "Frame.h"

#include <unordered_map>

#define CAMERA_SET 0
#define MODEL_SET 1
#define FRAGMENT_SET 2

namespace GLEEC::Graphics
{
    struct ShaderManager
    {
        GLEEC_API static void init(
            const std::vector<std::vector<std::string>>& shaderGroups);

        GLEEC_API static void init(std::string_view directory);

        GLEEC_API static void init();

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void bindShaders(const FrameData& frame, size_t shaders);
#endif

        GLEEC_API static void destroy();

        static Shaders& getShaders(std::string_view type)
        {
            return shaders[std::hash<std::string_view>{}(type)];
        }

        static Shaders& getShaders(size_t key)
        {
            return shaders[key];
        }

        GLEEC_API static std::unordered_map<size_t, Shaders> shaders;
    };
}
