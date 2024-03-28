#pragma once

#include "RenderTarget.h"

#include "Core/Window/WindowManager.h"

namespace GLEEC::Graphics
{
    struct RenderTargetManager
    {
        static void init()
        {
            for (uint32_t i : Window::WindowManager::availableWindows())
            {
                initRenderTarget(i);
            }
        }

        static void destroy()
        {
            for (int i = 0; i < renderTargets.size(); ++i)
            {
                destroyRenderTarget(i);
            }
        }

        GLEEC_API static void begin();
        GLEEC_API static void end();

        GLEEC_API static std::array<RenderTarget, GLEEC_WINDOW_MAX_WINDOWS> renderTargets;

        // needs to be accessible by window manager 
        GLEEC_API static void destroyRenderTarget(size_t i);
        GLEEC_API static void initRenderTarget(size_t i);

        static void recreateRenderTarget(size_t i)
        {
            destroyRenderTarget(i);
            initRenderTarget(i);
        }
    };
}
