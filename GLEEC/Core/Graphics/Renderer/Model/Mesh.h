#pragma once

#include "Vertex.h"
#include "Index.h"

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

        inline size_t vertexCount() const
        {
#if GLEEC_RENDERER_MESH_PERSIST_VERTICES
            return vertices.size();
#else
            return vertces;
#endif
        }

#if GLEEC_RENDERER_MESH_PERSIST_INDICES
        std::vector<Index> indices = {};
#else
        size_t indices = {};
#endif

        inline size_t indexCount() const
        {
#if GLEEC_RENDERER_MESH_PERSIST_VERTICES
            return indices.size();
#else
            return indces;
#endif
        }

        Material* material = {};

        Mesh() = default;
        Mesh(std::string_view Name)
            : name(Name)
        {
        }

        std::string name = "Unknown Mesh";
    };
}
