#pragma once

#include "Mesh.h"

#include "Core/Graphics/Renderer/ShaderResource.h"

namespace GLEEC::Graphics
{
    // TODO: have materials reference meshes instead of vice versa
    // that way descriptor set stuff is more efficient
    //
    // a geometry is a unique representation of data loaded once.
    // model is what has the rendering data stuff
    struct Geometry
    {
        std::vector<Mesh> meshes = {};

        std::vector<ColorMaterial> colorMaterials = {};
        std::vector<TextureMaterial> textureMaterials = {};

        std::string filepath = "";
    };
}
