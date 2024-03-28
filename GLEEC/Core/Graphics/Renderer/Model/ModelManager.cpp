#include "ModelManager.h"

#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/Renderer/ShaderManager.h"
#include "Core/Graphics/Renderer/Frame.h"
#include "Core/Graphics/Renderer/ShaderResourceManager.h"

#include "Core/Graphics/Camera/CameraManager.h"

namespace GLEEC::Graphics
{
    std::vector<std::vector<Model>> ModelManager::models(GLEEC_WINDOW_MAX_WINDOWS);

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    ShaderResource ModelManager::modelBuffer = {};
#endif

    inline void ModelManager::init()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        modelBuffer = ShaderResourceManager::createUniformBufferShaderResource(
            ShaderManager::getShaders("cl"), MODEL_SET);
#endif
    }

    inline void ModelManager::destroy()
    {
        for (size_t i = 0; i < models.size(); ++i)
        {
            destroyModels(i);
        }
    }

    void ModelManager::destroyModels(size_t i)
    {
        for (Model& model : models.at(i))
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::destroyBuffer(
                GPUManager::activeGPU.allocator,
                model.uniformBuffer.buffer);
#endif
        }
    }

    inline Model& ModelManager::createModel(Geometry& geometry, size_t i)
    {
        Model& model = models.at(i).emplace_back();
        model.geometry = &geometry;

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        model.model = math::mat4(1.0f);
        model.uniformBuffer = BufferManager::createUniformBuffer(
            sizeof(model.model), &model.model(0, 0));

        ShaderResourceManager::addUniformBuffer(modelBuffer, model.uniformBuffer);
#endif

        return model;
    }

    inline void ModelManager::renderModels()
    {
        for (uint32_t i : Window::WindowManager::availableWindows())
        {
            FrameData& frame = FrameManager::frame(i);

            CameraManager::useCamera(frame, CameraManager::defaultFPSCamera(Window::WindowManager::windows.at(i)));

            for (const Model& model : models.at(i))
            {
                BufferManager::updateUniformBuffer(model.uniformBuffer,
                    &model.model(0, 0));

                ShaderResourceManager::use(frame, modelBuffer, model.uniformBuffer);

                GeometryManager::drawGeometry(frame, *model.geometry);
            }
        }
    }
}
