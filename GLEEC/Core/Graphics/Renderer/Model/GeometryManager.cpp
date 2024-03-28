#include "GeometryManager.h"

#include "Core/Graphics/BufferManager.h"

#include "Core/Graphics/Renderer/ShaderResourceManager.h"
#include "Core/Graphics/Renderer/ShaderManager.h"

#include "parsers/obj.h"

namespace GLEEC::Graphics
{
    std::unordered_map<size_t, Geometry> GeometryManager::geometries = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    ShaderResource GeometryManager::colorResource = {};
    ShaderResource GeometryManager::textureResource = {};
#endif

    inline void GeometryManager::init()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        colorResource = ShaderResourceManager::createUniformBufferShaderResource(
            ShaderManager::getShaders("cl"), FRAGMENT_SET);

        textureResource = ShaderResourceManager::createCombinedImageShaderResource(
            ShaderManager::getShaders("uv"), FRAGMENT_SET);
#endif

        LOG_MESSAGE("should do geometry caching very soon");
    }

    inline void GeometryManager::destroy()
    {
        for (auto& [_, geometry] : geometries)
        {
            destroyGeometry(geometry);
        }
    }

    Geometry& GeometryManager::createGeometry(std::string_view filepath)
    {
        std::string filetype = std::string(filepath.substr(
            filepath.find_last_of('.') + 1));

        if (filetype == "obj")
        {
            return geometries[key(filepath)] = parsers::obj(filepath);
        }

        else
        {
            LOG_WARNING("Unknown filetype: {} when creating geometry: {}, loaded as empty!",
                filetype, filepath);

            return geometries[key(filepath)] = {};
        }
    }

    void GeometryManager::destroyGeometry(Geometry& geometry)
    {
        for (Mesh& mesh : geometry.meshes)
        {
            BufferManager::destroyBuffer(mesh.vertexBuffer);
            BufferManager::destroyBuffer(mesh.indexBuffer);

            for (ColorMaterial& material : geometry.colorMaterials)
            {
                BufferManager::destroyBuffer(material.colorBuffer);
            }
        }
    }

    inline void GeometryManager::drawGeometry(const FrameData& frame,
        const Geometry& geometry)
    {
        for (const Mesh& mesh : geometry.meshes)
        {
            BufferManager::bindVertexBuffer(frame.commandBuffer, mesh.vertexBuffer);
            BufferManager::bindIndexBuffer(frame.commandBuffer, mesh.indexBuffer);

            ShaderManager::bindShaders(frame, mesh.material->shaderClass);

            ShaderResourceManager::use(frame,mesh.material->type ==
                COLOR_MATERIAL ? colorResource : textureResource,
                mesh.material->offset);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            vkCmdDrawIndexed(frame.commandBuffer, mesh.indexCount(), 1, 0, 0, 0);
#endif
        }
    }
}
