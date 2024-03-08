#pragma once

#include "Vertex.h"
#include "Material.h"
#include "Core/Graphics/Buffer.h"

#define GLEEC_RENDERER_MESH_PERSIST_VERTICES 1
#define GLEEC_RENDERER_MESH_PERSIST_INDICES 1

#include <vector>

namespace GLEEC::Graphics
{
    struct Mesh
    {
        Buffer vertexBuffer = {};
        Buffer indexBuffer = {};

#if GLEEC_RENDERER_MESH_PERSIST_VERTICES
        std::vector<Vertex> vertices = {};
#else
        size_t vertices = {};
#endif

#if GLEEC_RENDERER_MESH_PERSIST_INDICES
        std::vector<uint32_t> indices = {};
#else
        size_t indices = {};
#endif

        Material* material = {};

        std::string name = "Unknown Mesh";
    };
}
