#pragma once

#include "Config/Export.h"

#include "Core/Graphics/Frame.h"
#include "Geometry.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/DescriptorBuffer.h"
#endif

#include <unordered_map>

namespace GLEEC::Graphics
{
    struct GeometryManager
    {
        static Geometry& findGeometry(std::string_view filepath)
        {
            if (models.contains(key(filepath)))
            {
                return models.at(key(filepath));
            }

            return createGeometry(filepath);
        }

        static void destroy()
        {
            for (auto& [_, model] : models)
            {
                destroyGeometry(model);
            }
        }

        static constexpr uint32_t uniformBuffer = 0;
        static constexpr uint32_t colorBuffer = 1;
        static constexpr uint32_t textureBuffer = 2;

        GLEEC_API static void drawGeometry(const FrameData& frame,
            const Geometry& geometry, VkDeviceSize uniformBufferOffset);

        GLEEC_API static std::unordered_map<size_t, Geometry> models;

    private:
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static Internal::Graphics::vk::DescriptorBuffer modelBuffer;
#endif

        GLEEC_API static Geometry& createGeometry(std::string_view filepath);
        GLEEC_API static void destroyGeometry(Geometry& model);

        static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
