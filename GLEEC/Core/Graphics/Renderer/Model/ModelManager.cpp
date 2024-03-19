#include "ModelManager.h"

#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/ShaderManager.h"
#include "Core/Graphics/FrameManager.h"

namespace GLEEC::Graphics
{
    std::vector<Model> ModelManager::models = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    Internal::Graphics::vk::DescriptorBuffer ModelManager::modelBuffer = {};
#endif

    inline void ModelManager::init()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        modelBuffer = Internal::Graphics::vk::createDescriptorBuffer(
            GPUManager::activeGPU.device.physicalDevice,
            GPUManager::activeGPU.device,
            GPUManager::activeGPU.allocator,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0,
            ShaderManager::getShaders("cl").descriptorSetLayouts.at(
                GeometryManager::uniformBuffer));
#endif
    }

    inline void ModelManager::destroy()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyDescriptorBuffer(
            GPUManager::activeGPU.allocator, modelBuffer);
#endif

        for (Model& model : models)
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::destroyBuffer(
                GPUManager::activeGPU.allocator,
                model.uniformBuffer.buffer);
#endif
        }
    }

    inline Model& ModelManager::createModel(Geometry& geometry)
    {
        Model& model = models.emplace_back();
        model.geometry = &geometry;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        model.model = math::mat4(1.0f);
        model.uniformBuffer = BufferManager::createUniformBuffer(
            sizeof(model.model), &model.model(0, 0));

        model.bufferIndex = Internal::Graphics::vk::getUniformBufferDescriptor(
            GPUManager::activeGPU.device.physicalDevice,
            GPUManager::activeGPU.device,
            GPUManager::activeGPU.allocator,
            modelBuffer, model.uniformBuffer.buffer);
#endif

        return model;
    }

    inline void ModelManager::renderModels(const FrameData& frame)
    {
        for (const Model& model : models)
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            std::vector<Internal::Graphics::vk::DescriptorBuffer> descriptorBuffers(3);

            descriptorBuffers[GeometryManager::uniformBuffer] = modelBuffer;
            descriptorBuffers[GeometryManager::colorBuffer] =
                model.geometry->colorDescriptorBuffer;
            descriptorBuffers[GeometryManager::textureBuffer] =
                model.geometry->textureDescriptorBuffer;

            memcpy_s(model.uniformBuffer.buffer.map, sizeof(model.model),
                &model.model(0, 0), sizeof(model.model));

            Internal::Graphics::vk::cmdBindDescriptorBuffers(
                GPUManager::activeGPU.device,
                frame.commandBuffer, descriptorBuffers);
#endif

            GeometryManager::drawGeometry(frame, *model.geometry,
                model.bufferIndex);
        }
    }

    inline void ModelManager::renderModels(const Frame& frame)
    {
#if GLEEC_USE_FRAMES_IN_FLIGHT
        renderModels(frame.frames[FrameManager::activeFrame]);
#else
        renderModels(frame.frame);
#endif
    }

    inline void ModelManager::renderModels(size_t i)
    {
        renderModels(FrameManager::frames[i]);
    }
}
