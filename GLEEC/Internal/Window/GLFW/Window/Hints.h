#pragma once

#include "Window.h"

namespace GLEEC::Internal::Window::glfw
{
    inline void defaultWindowHints()
    {
        glfwDefaultWindowHints();
    }

    inline void windowHint(int hint, int value)
    {
        glfwWindowHint(hint, value);
    }

    inline void windowHintString(int hint, const char* value)
    {
        glfwWindowHintString(hint, value);
    }

    inline int getWindowAttrib(Window window, int attrib)
    {
        return glfwGetWindowAttrib(window, attrib);
    }

    inline void setWindowAttrib(Window window, int attrib, int value)
    {
        glfwSetWindowAttrib(window, attrib, value);
    }
}
