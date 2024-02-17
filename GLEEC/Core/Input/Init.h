#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Input/GLFW/Init.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

namespace GLEEC::Input
{
    inline void init()
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::init();
#endif

        JoystickManager::init();
    }

    inline void terminate()
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::terminate();
#endif
    }
}
