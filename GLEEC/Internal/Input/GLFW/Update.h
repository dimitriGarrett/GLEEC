#pragma once

#include "Internal/Input/Backends/GLFW.h"

namespace GLEEC::Internal::Input::glfw
{
    inline void pollEvents()
    {
        glfwPollEvents();
    }

    inline void waitEvents()
    {
        glfwWaitEvents();
    }

    inline void waitEventsTimeout(double timeout)
    {
        glfwWaitEventsTimeout(timeout);
    }

    inline void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }

    // swap buffers not implemented as this is vulkan territory,
    // we dont use that slimy OPENGL stuff (anymore ahaha)
}
