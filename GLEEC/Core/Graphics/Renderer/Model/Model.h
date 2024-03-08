#pragma once

#include "Mesh.h"

namespace GLEEC::Graphics
{
    struct Model
    {
        std::vector<Mesh> meshes = {};
        std::vector<Material> materials = {};

        std::string filepath = "";
    };
}
