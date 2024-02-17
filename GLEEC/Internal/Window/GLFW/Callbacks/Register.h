#pragma once

#include "Monitor.h"
#include "Window.h"

namespace GLEEC::Internal::Window::glfw
{
    inline void setWindowCallbacks(Window window)
    {
        setAllWindowCallbacks(window);
    }
}
