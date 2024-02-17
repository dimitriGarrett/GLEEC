#pragma once

#include "Internal/Window/GLFW/Window/Window.h"

#include "Internal/Event/Subway.h"
#include "Internal/Window/Events.h"

#include "Internal/Log/EnableInternalLogging"

namespace GLEEC::Internal::Window::glfw
{
    using WindowPosCallback = void(*)(GLFWwindow*, int, int);
    using WindowSizeCallback = void(*)(GLFWwindow*, int, int);
    using WindowCloseCallback = void(*)(GLFWwindow*);
    using WindowRefreshCallback = void(*)(GLFWwindow*);
    using WindowFocusCallback = void(*)(GLFWwindow*, int);
    using WindowIconifyCallback = void(*)(GLFWwindow*, int);
    using WindowMaximizeCallback = void(*)(GLFWwindow*, int);
    using FramebufferSizeCallback = void(*)(GLFWwindow*, int, int);
    using WindowContentScaleCallback = void(*)(GLFWwindow*, float, float);

    inline void setWindowPosCallback(Window window)
    {
        glfwSetWindowPosCallback(window, +[](GLFWwindow* w, int x, int y)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) pos: ({}, {})", static_cast<void*>(w), x, y);
#endif
            Event::fireEvent<Events::WindowPosEvent>(w, x, y);
        });
    }

    inline void setWindowSizeCallback(Window window)
    {
        glfwSetWindowSizeCallback(window, +[](GLFWwindow* w, int x, int y)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) size: ({}, {})", static_cast<void*>(w), x, y);
#endif
            Event::fireEvent<Events::WindowResizeEvent>(w, x, y);
        });
    }

    inline void setWindowCloseCallback(Window window)
    {
        glfwSetWindowCloseCallback(window, +[](GLFWwindow* w)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) closed!", static_cast<void*>(w));
#endif
            Event::fireEvent<Events::WindowCloseEvent>(w);

            destroyWindow(w);
        });
    }

    inline void setWindowRefreshCallback(Window window)
    {
        glfwSetWindowRefreshCallback(window, +[](GLFWwindow* w)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) refreshed!", static_cast<void*>(w));
#endif
            Event::fireEvent<Events::WindowRefreshEvent>(w);
        });
    }

    inline void setWindowFocusCallback(Window window)
    {
        glfwSetWindowFocusCallback(window, +[](GLFWwindow* w, int focus)
        {
            if (focus)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) gained focus!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::WindowFocusEvent>(w);
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) lost focus!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::WindowLostFocusEvent>(w);
            }
        });
    }

    inline void setWindowIconifyCallback(Window window)
    {
        glfwSetWindowIconifyCallback(window, +[](GLFWwindow* w, int iconified)
        {
            if (iconified)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) iconified!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::WindowIconifyEvent>(w);
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) restored!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::WindowRestoreEvent>(w);
            }
        });
    }

    inline void setWindowMaximizeCallback(Window window)
    {
        glfwSetWindowMaximizeCallback(window, +[](GLFWwindow* w, int maximized)
        {
            if (maximized)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) maximized!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::WindowMaximizeEvent>(w);
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Window: {}) unmaximized!", static_cast<void*>(w));
#endif
                Event::fireEvent<Events::WindowUnmaximizeEvent>(w);
            }
        });
    }

    inline void setFramebufferSizeCallback(Window window)
    {
        glfwSetFramebufferSizeCallback(window, +[](GLFWwindow* w, int width, int height)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) framebuffer size: ({}, {})", static_cast<void*>(w), width, height);
#endif
            Event::fireEvent<Events::FramebufferSizeEvent>(w, width, height);
        });
    }

    inline void setWindowContentScaleCallback(Window window)
    {
        glfwSetWindowContentScaleCallback(window, +[](GLFWwindow* w, float width, float height)
        {
#if GLEEC_ALL_INTERNAL_LOGGING
            LOG_INFO("(Window: {}) content scale: ({}, {})", static_cast<void*>(w), width, height);
#endif
            Event::fireEvent<Events::WindowContentScaleEvent>(w, width, height);
        });
    }

    inline void setAllWindowCallbacks(Window window)
    {
        setWindowPosCallback(window);
        setWindowSizeCallback(window);
        setWindowCloseCallback(window);
        setWindowRefreshCallback(window);
        setWindowFocusCallback(window);
        setWindowIconifyCallback(window);
        setWindowMaximizeCallback(window);
        setFramebufferSizeCallback(window);
        setWindowContentScaleCallback(window);
    }
}
