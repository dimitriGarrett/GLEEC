#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Mouse.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "State.h"

namespace GLEEC::Input
{
    inline bool isMouseButtonPressed(int32_t mouseButton)
    {
        Remapper& rp = Remapper::currentPreset();

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return detail::isStatePressed(rp.unmap(mouseButton));
#else
        return false;
#endif
    }

    inline bool isMouseButtonReleased(int32_t mouseButton)
    {
        return !isMouseButtonPressed(mouseButton);
    }
}
