#pragma once

#include "Internal/Window/Window.h"

namespace GLEEC::Internal::Input::glfw
{
    inline int getInputMode(Window::glfw::Window window, int mode)
    {
        return glfwGetInputMode(window, mode);
    }

    inline void setInputMode(Window::glfw::Window window, int mode, int value)
    {
        glfwSetInputMode(window, mode, value);
    }
}
