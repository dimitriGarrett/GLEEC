#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Update.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

namespace GLEEC::Input
{
    inline void update()
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::pollEvents();
#endif
    }
}
