#pragma once

#include "Config/Export.h"
#include "Core/Graphics/Frame.h"

#include "GeometryManager.h"
#include "Model.h"

namespace GLEEC::Graphics
{
    struct ModelManager
    {
        static Model& createModel(std::string_view filepath)
        {
            return createModel(GeometryManager::findGeometry(filepath));
        }

        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void renderModels(const FrameData& frame);
        GLEEC_API static void renderModels(const Frame& frame);

        GLEEC_API static void renderModels(size_t index);

        // the default place to render is the first window (main window)
        static void renderModels()
        {
            renderModels(0);
        }

        GLEEC_API static std::vector<Model> models;

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static Internal::Graphics::vk::DescriptorBuffer modelBuffer;
#endif

        GLEEC_API static Model& createModel(Geometry& geometry);

        static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
