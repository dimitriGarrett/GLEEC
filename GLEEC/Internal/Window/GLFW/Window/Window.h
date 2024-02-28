#pragma once

#include "Internal/Window/Events.h"
#include "Internal/Window/Monitor.h"

namespace GLEEC::Internal::Window::glfw
{
    using Window = GLFWwindow*;

    // share is omitted because that only applies to OpenGL
    inline Window createWindow(const math::ivec2& dimensions, std::string_view title, Monitor monitor = nullptr)
    {
        Window temp = { glfwCreateWindow(dimensions.x, dimensions.y, title.data(), monitor, nullptr) };

        return temp;
    }

    inline void destroyWindow(Window window)
    {
        glfwDestroyWindow(window);
    }

    // these were originally bools, but looking at the docs (https://www.glfw.org/docs/latest/moving.html)
    // shows it can be useful for other things, like closing the window from a button
    inline int windowShouldClose(Window window)
    {
        // i want to use logical or but since glfwWindowShouldClose can return other values other than 0 and 1 it wouldn't work properly :(
        // return window == nullptr || glfwWindowShouldClose(window);
        return (window == nullptr) ? 1 : glfwWindowShouldClose(window);
    }

    inline void setWindowShouldClose(Window window, int value)
    {
        glfwSetWindowShouldClose(window, value);
    }

    inline void setWindowTitle(Window window, std::string_view title)
    {
        glfwSetWindowTitle(window, title.data());
    }

    inline void resetWindowTitle(Window window)
    {
        setWindowTitle(window, "Window");
    }

    inline math::ivec2 getWindowPos(Window window)
    {
        math::ivec2 temp = {};
        glfwGetWindowPos(window, &temp.x, &temp.y);
        return temp;
    }

    inline void setWindowPos(Window window, const math::ivec2& pos)
    {
        glfwSetWindowPos(window, pos.x, pos.y);
    }

    inline math::ivec2 getWindowSize(Window window)
    {
        math::ivec2 temp = {};
        glfwGetWindowSize(window, &temp.x, &temp.y);
        return temp;
    }

    inline void setWindowSizeLimits(Window window, const math::ivec4& minmax)
    {
        glfwSetWindowSizeLimits(window, minmax.x, minmax.y, minmax.x, minmax.y);
    }

    inline void setWindowAspectRatio(Window window, int numer, int denom)
    {
        glfwSetWindowAspectRatio(window, numer, denom);
    }

    inline void setWindowSize(Window window, const math::ivec2& size)
    {
        glfwSetWindowSize(window, size.x, size.y);
    }

    inline math::ivec2 getFramebufferSize(Window window)
    {
        math::ivec2 temp = {};
        glfwGetFramebufferSize(window, &temp.x, &temp.y);
        return temp;
    }

    inline math::ivec4 getWindowFrameSize(Window window)
    {
        math::ivec4 temp = {};
        glfwGetWindowFrameSize(window, &temp.x, &temp.y, &temp.z, &temp.w);
        return temp;
    }

    inline math::fvec2 getWindowContentScale(Window window)
    {
        math::fvec2 temp = {};
        glfwGetWindowContentScale(window, &temp.x, &temp.y);
        return temp;
    }

    inline float getWindowOpacity(Window window)
    {
        return glfwGetWindowOpacity(window);
    }

    inline void setWindowOpacity(Window window, float opacity)
    {
        glfwSetWindowOpacity(window, opacity);
    }

    inline void iconifyWindow(Window window)
    {
        glfwIconifyWindow(window);
    }

    inline void restoreWindow(Window window)
    {
        glfwRestoreWindow(window);
    }

    inline void maximizeWindow(Window window)
    {
        glfwMaximizeWindow(window);
    }

    inline void showWindow(Window window)
    {
        glfwShowWindow(window);
    }

    inline void hideWindow(Window window)
    {
        glfwHideWindow(window);
    }

    inline void focusWindow(Window window)
    {
        glfwFocusWindow(window);
    }

    inline void requestWindowAttention(Window window)
    {
        glfwRequestWindowAttention(window);
    }

    inline Monitor getWindowMonitor(Window window)
    {
        return glfwGetWindowMonitor(window);
    }

    inline void setWindowMonitor(Window window, Monitor monitor,
        const math::ivec2& pos, const math::ivec2& size, int refreshRate)
    {
        glfwSetWindowMonitor(window, monitor, pos.x, pos.y, size.x, size.y, refreshRate);
    }

    inline void setWindowMonitor(Window window, Monitor monitor,
        const math::ivec2& pos, const math::ivec2& size)
    {
        glfwSetWindowMonitor(window, monitor, pos.x, pos.y, size.x, size.y, GLFW_DONT_CARE);
    }

    inline void setWindowUserPointer(Window window, void* data)
    {
        glfwSetWindowUserPointer(window, data);
    }

    inline void* getWindowUserPointer(Window window)
    {
        return glfwGetWindowUserPointer(window);
    }
}
