#pragma once

#include "Core/Graphics/Renderer/FrameManager.h"

#include "GeometryManager.h"
#include "Model.h"

namespace GLEEC::Graphics
{
    struct ModelManager
    {
        static Model& createModel(std::string_view filepath, size_t i = 0)
        {
            return createModel(GeometryManager::findGeometry(filepath), i);
        }

        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void destroyModels(size_t i);

        GLEEC_API static void renderModels();

        GLEEC_API static std::vector<std::vector<Model>> models;

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static ShaderResource modelBuffer;
#endif

        GLEEC_API static Model& createModel(Geometry& geometry, size_t i);

        static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
