#pragma once

#include "Core/Graphics/Renderer/Frame.h"
#include "Shaders.h"

#include <unordered_map>

namespace GLEEC::Graphics
{
    struct ShaderManager
    {
        GLEEC_API static void init(
            const std::vector<std::vector<std::string>>& shaderGroups);
        GLEEC_API static void init(std::string_view shader_directory);
        GLEEC_API static void init();

        GLEEC_API static void destroy();

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void bindShaders(const FrameData& frame,
            size_t shaders);
#endif

        static Shaders& getShaders(std::string_view type)
        {
            return shaders[std::hash<std::string_view>{}(type)];
        }

        static Shaders& getShaders(size_t key)
        {
            return shaders[key];
        }

        GLEEC_API static std::unordered_map<size_t, Shaders> shaders;

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static void loadShadersBindings(Shaders& shaders,
            const std::vector<std::string>& grouped);
#endif

        GLEEC_API static void loadShaders(Shaders& shaders,
            const std::vector<std::string>& grouped);

        GLEEC_API static void createShaders(Shaders& shaders,
            const std::vector<std::string>& grouped);

        GLEEC_API static void destroyShaders(Shaders& shaders);
    };
}
