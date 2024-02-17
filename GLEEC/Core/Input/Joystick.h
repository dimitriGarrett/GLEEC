#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Joystick.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "State.h"

namespace GLEEC::Input
{
    struct Joystick
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        Internal::Input::glfw::Joystick internalJoystick = {};

        Joystick() = default;
        Joystick(int jid)
            : internalJoystick(jid)
        {
        }
#endif

        bool operator==(const Joystick&) const = default;
        bool operator!=(const Joystick&) const = default;

        std::string_view name() const
        {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
            return Internal::Input::glfw::getJoystickName(internalJoystick);
#else
            return "Unknown Joystick Name!";
#endif
        }

        bool buttonPressed(int32_t button) const
        {
            Remapper& rp = Remapper::currentPreset();

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
            return detail::isStatePressed(internalJoystick, rp.unmap(button));
#else
            return false;
#endif
        }

        bool buttonReleased(int32_t button) const
        {
            return !buttonPressed(button);
        }

        float axis(int32_t axis) const
        {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
            return Internal::Input::glfw::getGamepadAxes(internalJoystick)[axis];
#else
            return 0.0f;
#endif
        }
    };
}
