#pragma once

#include "Core/Graphics/ShaderManager.h"
#include "FrameManager.h"
#include "InstanceManager.h"
#include "RenderTargetManager.h"

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
    }

    inline void terminate()
    {
        GPUManager::activeGPU.wait();

        ShaderManager::destroy();
        FrameManager::destroy();
        RenderTargetManager::destroy();

        GPUManager::closeGPU();
        InstanceManager::destroyInstance();
    }
}
