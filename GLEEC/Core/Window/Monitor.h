#pragma once

#include "Internal/Window/Backend.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Window/GLFW/Monitor.h"
#else
#error "Unknown Window backend for GLEEC!"
#endif

namespace GLEEC::Window
{
    struct Monitor
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Window::glfw::Monitor internalMonitor = {};
#endif

        math::ivec2 pos() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return Internal::Window::glfw::getMonitorPos(internalMonitor);
#else
            return { 0, 0 };
#endif
        }

        math::ivec2 size() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            auto videomode = Internal::Window::glfw::getMonitorVideoMode(internalMonitor);

            return { videomode.width, videomode.height };
#else
            return { 0, 0 };
#endif
        }

        std::string_view name() const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            return Internal::Window::glfw::getMonitorName(internalMonitor);
#else
            return "Unknown Monitor Name!";
#endif
        }

        void gamma(float g) const
        {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
            Internal::Window::glfw::setMonitorGamma(internalMonitor, g);
#endif
        }
    };
}
