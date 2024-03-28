#include "Renderer.h"
#include "Core/Graphics/Renderer/ShaderManager.h"
#include "FrameManager.h"
#include "RenderTargetManager.h"
#include "ShaderResourceManager.h"

#include "Model/ModelManager.h"

#include "Core/Window/WindowManager.h"
#include "Core/Graphics/Camera/CameraManager.h"

namespace GLEEC::Graphics
{
    inline void Renderer::init()
    {
        ShaderManager::init();
        ShaderResourceManager::init();

        GeometryManager::init();
        ModelManager::init();
    }

    inline void Renderer::destroy()
    {
        ModelManager::destroy();
        GeometryManager::destroy();

        ShaderResourceManager::destroy();
        ShaderManager::destroy();
    }

    inline void Renderer::begin()
    {
        Window::WindowManager::begin();
        FrameManager::begin();
        RenderTargetManager::begin();
    }

    inline void Renderer::draw()
    {
        // updates camera buffers and also the descriptor buffer
        CameraManager::updateCameras();

        // actually draws
        ModelManager::renderModels();
    }

    inline void Renderer::end()
    {
        RenderTargetManager::end();
        FrameManager::end();
    }
}
