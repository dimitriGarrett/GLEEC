#pragma once

#include "Internal/Window/Window.h"

namespace GLEEC::Internal::Input::glfw
{
    inline bool isRawMouseMotionSupported()
    {
        return glfwRawMouseMotionSupported();
    }

    inline bool getMouseButton(Window::glfw::Window window, int32_t button)
    {
        // this doesn't differentiate between repeat and press
        return glfwGetMouseButton(window, button);
    }
}
