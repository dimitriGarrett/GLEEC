#pragma once

#include "BufferManager.h"
#include "ShaderManager.h"

#include "FrameManager.h"
#include "InstanceManager.h"
#include "RenderTargetManager.h"

#include "Renderer/Init.h"

namespace GLEEC::Graphics
{
    inline void firstInit()
    {
        InstanceManager::createInstance();
    }

    inline void init()
    {
        GPUManager::selectGPU();

        for (Window::Window& window : Window::WindowManager::windows)
        {
            if (window.isOpen())
                Window::WindowManager::finalizeWindow(window);
        }

        FrameManager::init();
        RenderTargetManager::init();

        BufferManager::init();
        ShaderManager::init();

        initRenderer();
    }

    inline void destroy()
    {
        GPUManager::activeGPU.wait();

        ShaderManager::destroy();
        FrameManager::destroy();
        RenderTargetManager::destroy();

        BufferManager::destroy();

        destroyRenderer();

        GPUManager::closeGPU();
        InstanceManager::destroyInstance();
    }
}
