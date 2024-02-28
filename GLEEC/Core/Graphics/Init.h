#pragma once

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

        FrameManager::destroy();
        RenderTargetManager::destroy();

        GPUManager::closeGPU();
        InstanceManager::destroyInstance();
    }
}
