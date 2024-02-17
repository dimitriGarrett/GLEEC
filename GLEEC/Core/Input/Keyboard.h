#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Keyboard.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "State.h"

namespace GLEEC::Input
{
    inline std::string_view keyName(int32_t key)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return Internal::Input::glfw::getKeyName(key);
#else
        return "Unknown Key Name!";
#endif
    }

    inline bool isKeyPressed(int32_t key)
    {
        Remapper& rp = Remapper::currentPreset();

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return detail::isStatePressed(rp.unmap(key));
#else
        return false;
#endif
    }

    inline bool isKeyReleased(int32_t key)
    {
        return !isKeyPressed(key);
    }
}
