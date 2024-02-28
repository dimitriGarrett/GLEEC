#pragma once

#include "RenderTarget.h"

#include "Core/Window/WindowManager.h"

namespace GLEEC::Graphics
{
    struct RenderTargetManager
    {
        static void init()
        {
            for (int i = 0; i < Window::WindowManager::openWindows; ++i)
            {
                initRenderTarget(i);
            }
        }

        static void destroy()
        {
            for (int i = 0; i < Window::WindowManager::openWindows; ++i)
            {
                destroyRenderTarget(i);
            }
        }

        GLEEC_API static std::array<RenderTarget, GLEEC_WINDOW_MAX_WINDOWS> renderTargets;

        // needs to be accessible by window manager 
        GLEEC_API static void destroyRenderTarget(size_t i);
        GLEEC_API static void initRenderTarget(size_t i);

        static void recreateRenderTarget(size_t i)
        {
            destroyRenderTarget(i);
            initRenderTarget(i);
        }

        static void swap(size_t a, size_t b)
        {
            RenderTarget&& fa = std::move(renderTargets[a]);
            renderTargets[a] = std::move(renderTargets[b]);
            renderTargets[b] = std::move(fa);
        }
    };
}
