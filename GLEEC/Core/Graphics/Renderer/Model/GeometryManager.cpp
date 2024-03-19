#include "GeometryManager.h"
#include "MeshManager.h"

#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/GPUManager.h"
#include "Core/Graphics/ShaderManager.h"

#include "parsers/obj.h"

namespace GLEEC::Graphics
{
    std::unordered_map<size_t, Geometry> GeometryManager::models = {};

    Geometry& GeometryManager::createGeometry(std::string_view filepath)
    {
        std::string filetype = std::string(filepath.substr(
            filepath.find_last_of('.') + 1));

        if (filetype == "obj")
        {
            return models[key(filepath)] = parsers::obj(filepath);
        }

        else
        {
            LOG_WARNING("Unknown filetype: {} when creating model: {}, loaded as empty!",
                filetype, filepath);

            return models[key(filepath)] = {};
        }
    }

    void GeometryManager::destroyGeometry(Geometry& model)
    {
        for (Mesh& mesh : model.meshes)
        {
            BufferManager::destroyBuffer(mesh.vertexBuffer);
            BufferManager::destroyBuffer(mesh.indexBuffer);

            for (ColorMaterial& material : model.colorMaterials)
            {
                BufferManager::destroyBuffer(material.colorBuffer);
            }

            for (TextureMaterial& material : model.textureMaterials)
            {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
                Internal::Graphics::vk::destroyImageView(
                    GPUManager::activeGPU.device,
                    material.imageView);

                Internal::Graphics::vk::destroySampler(
                    GPUManager::activeGPU.device,
                    material.sampler);
#endif
            }
        }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::destroyDescriptorBuffer(
                GPUManager::activeGPU.allocator, model.colorDescriptorBuffer);
            Internal::Graphics::vk::destroyDescriptorBuffer(
                GPUManager::activeGPU.allocator, model.textureDescriptorBuffer);
#endif
    }

    void GeometryManager::drawGeometry(const FrameData& frame,
        const Geometry& geometry, VkDeviceSize uniformBufferOffset)
    {
        for (const Mesh& mesh : geometry.meshes)
        {
            BufferManager::bindVertexBuffer(frame.commandBuffer, mesh.vertexBuffer);
            BufferManager::bindIndexBuffer(frame.commandBuffer, mesh.indexBuffer);

            ShaderManager::bindShaders(frame, mesh.material->shaderClass);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::PipelineLayout& layout =
                ShaderManager::getShaders(mesh.material->shaderClass).pipelineLayout;

            Internal::Graphics::vk::cmdSetGraphicsPipelineDescriptorBufferOffsets(
                frame.commandBuffer, layout, MODEL_SET, 1,
                uniformBuffer, uniformBufferOffset);

            Internal::Graphics::vk::cmdSetGraphicsPipelineDescriptorBufferOffsets(
                frame.commandBuffer, layout, FRAGMENT_SET, 1, 
                mesh.material->buffer(colorBuffer, textureBuffer),
                mesh.material->offset);
#endif

            mesh.material->bind();

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            vkCmdDrawIndexed(frame.commandBuffer, mesh.indexCount(), 1, 0, 0, 0);
#endif
        }
    }
}
