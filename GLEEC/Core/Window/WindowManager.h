#pragma once

#include "Window.h"

// this can always change in the future, but there is no reason
// to increase this for now
#define GLEEC_WINDOW_MAX_WINDOWS 3

#include <array>

namespace GLEEC::Window
{
    struct WindowManager
    {
        static Window& createWindow(const WindowInfo& info)
        {
            return (windows[openWindows >= GLEEC_WINDOW_MAX_WINDOWS ? GLEEC_WINDOW_MAX_WINDOWS : openWindows++] = Window(info));
        }

        static Window& activeWindow()
        {
            return windows.front();
        }

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        static Window& findWindow(const Internal::Window::glfw::Window& win)
        {
            for (Window& w : windows)
            {
                if (w.internalWindow == win) return w;
            }

            return windows.front();
        }
#endif

        GLEEC_API static void registerCallbacks();

        static bool anyOpen()
        {
            return openWindows > 0;
        }

        GLEEC_API static int openWindows;
        GLEEC_API static std::array<Window, GLEEC_WINDOW_MAX_WINDOWS> windows;
    };
}
