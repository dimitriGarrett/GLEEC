#pragma once

#include "Internal/Window/Window.h"

namespace GLEEC::Internal::Input::glfw
{
    inline math::dvec2 getCursorPos(Window::glfw::Window window)
    {
        math::dvec2 temp = {};
        glfwGetCursorPos(window, &temp.x, &temp.y);
        return temp;
    }

    inline void setCursorPos(Window::glfw::Window window, const math::dvec2& pos)
    {
        glfwSetCursorPos(window, pos.x, pos.y);
    }
}
