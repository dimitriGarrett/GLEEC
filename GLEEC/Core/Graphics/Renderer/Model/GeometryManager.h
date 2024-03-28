#pragma once

#include "Config/Export.h"

#include "Core/Graphics/Renderer/Frame.h"
#include "Geometry.h"

#include <unordered_map>

namespace GLEEC::Graphics
{
    struct GeometryManager
    {
        static Geometry& findGeometry(std::string_view filepath)
        {
            if (geometries.contains(key(filepath)))
            {
                return geometries.at(key(filepath));
            }

            return createGeometry(filepath);
        }

        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void drawGeometry(const FrameData& frame,
            const Geometry& geometry);

        GLEEC_API static std::unordered_map<size_t, Geometry> geometries;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        GLEEC_API static ShaderResource colorResource;
        GLEEC_API static ShaderResource textureResource;
#endif

    private:
        GLEEC_API static Geometry& createGeometry(std::string_view filepath);
        GLEEC_API static void destroyGeometry(Geometry& geometry);

        static size_t key(std::string_view filepath)
        {
            return std::hash<std::string_view>{}(filepath);
        }
    };
}
