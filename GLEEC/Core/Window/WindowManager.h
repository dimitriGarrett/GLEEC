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
        GLEEC_API static Window& createWindow(const WindowInfo& info);
        GLEEC_API static void destroyWindow(Window& window);
        
        GLEEC_API static void finalizeWindow(Window& window);

        static Window& activeWindow()
        {
            return windows[currentWindow];
        }

        static void init()
        {
            registerCallbacks();
        }

        static void destroy()
        {
            for (int i = 0; i < openWindows; ++i)
            {
                destroyWindow(i);
            }
        }

        static bool anyOpen()
        {
            return openWindows > 0;
        }

        static std::vector<Window*> renderableWindows()
        {
            std::vector<Window*> temp = {};

            for (size_t i = 0; i < openWindows; ++i)
            {
                if (!windows[i].minimized) temp.push_back(&windows[i]);
            }

            return temp;
        }

        static std::vector<size_t> renderableWindowIndices()
        {
            std::vector<size_t> temp = {};

            for (size_t i = 0; i < openWindows; ++i)
            {
                if (!windows[i].minimized) temp.push_back(i);
            }

            return temp;
        }

        GLEEC_API static size_t openWindows;
        GLEEC_API static size_t currentWindow;
        GLEEC_API static std::array<Window, GLEEC_WINDOW_MAX_WINDOWS> windows;

        GLEEC_API static size_t findWindowIndex(Window window);

        static size_t findWindowIndex(Window* window)
        {
            for (size_t i = 0; i < GLEEC_WINDOW_MAX_WINDOWS; ++i)
            {
                if (&windows[i] == window) return i;
            }

            return -1;
        }
    private:
        GLEEC_API static void swap(Window&, Window&);

        static void destroyWindow(int i)
        {
            destroyWindow(windows[i]);
        }

        GLEEC_API static void registerCallbacks();
    };
}
