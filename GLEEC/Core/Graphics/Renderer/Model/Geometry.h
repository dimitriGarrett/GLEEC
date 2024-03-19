#pragma once

#include "Mesh.h"

namespace GLEEC::Graphics
{
    // a geometry is a unique representation of data loaded once.
    // model is what has the rendering data stuff
    struct Geometry
    {
        std::vector<Mesh> meshes = {};

        std::vector<ColorMaterial> colorMaterials = {};
        std::vector<TextureMaterial> textureMaterials = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::DescriptorBuffer colorDescriptorBuffer = {};
        Internal::Graphics::vk::DescriptorBuffer textureDescriptorBuffer = {};
#endif

        std::string filepath = "";
    };
}
