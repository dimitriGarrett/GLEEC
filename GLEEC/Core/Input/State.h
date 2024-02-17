#pragma once

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Keyboard.h"
#include "Internal/Input/GLFW/Mouse.h"
#include "Internal/Input/GLFW/Joystick.h"
#include "Internal/Input/GLFW/Codes/Mods.h"
#include "Internal/Input/GLFW/Codes/Key.h"
#include "Internal/Input/GLFW/Codes/Gamepad.h"
#include "Internal/Input/GLFW/Codes/MouseButton.h"
#else
#error "Unknown Input backend for GLEEC!"
#endif

#include "Core/Window/WindowManager.h"
#include "Core/Input/Remapping/Remapper.h"

namespace GLEEC::Input::detail
{
    inline bool isKeyPressed(int32_t key)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return key != -1 && Internal::Input::glfw::getKey(
            Window::WindowManager::activeWindow().internalWindow,
            key);
#else
        return false;
#endif
    }

    inline bool isMouseButtonPressed(int32_t button)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return button != -1 && Internal::Input::glfw::getMouseButton(
            Window::WindowManager::activeWindow().internalWindow,
            button);
#else
        return false;
#endif
    }

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
    inline bool isGamepadButtonPressed(int jid, int32_t button)
    {
        return button != -1 && Internal::Input::glfw::getGamepadButtons(jid)[button - GAMEPAD_BUTTON_A];
    }
#endif

    inline bool isGamepadButtonPressed(int32_t button)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        for (int i = 0; i < GLFW_JOYSTICK_LAST; ++i)
        {
            if (Internal::Input::glfw::joystickPresent(i) && isGamepadButtonPressed(i, button))
            {
                return true;
            }
        }
#endif

        return false;
    }

#define CHECK_MOD(mod, a, b)\
    ((mod & state.mods) ? isKeyPressed(a) || detail::isKeyPressed(b) : true)

#define CHECK_MOD1(mod, a)\
    ((mod & state.mods) ? isKeyPressed(a) : true)

    inline bool areModsPressed(const RemapState& state)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return CHECK_MOD(MODIFIER_SHIFT, KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT) && 
               CHECK_MOD(MODIFIER_CONTROL, KEY_LEFT_CONTROL, KEY_RIGHT_CONTROL) &&
               CHECK_MOD(MODIFIER_ALT, KEY_LEFT_ALT, KEY_RIGHT_ALT) &&
               CHECK_MOD1(MODIFIER_CAPS_LOCK, KEY_CAPS_LOCK) &&
               CHECK_MOD1(MODIFIER_NUM_LOCK, KEY_NUM_LOCK);
#else
        return false;
#endif
    }

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
    inline bool isStatePressed(int jid, const RemapState& state)
    {
        if (!areModsPressed(state)) return false;

        if (state.state <= MOUSE_BUTTON_LAST)
        {
            return isMouseButtonPressed(state.state);
        }

        else if (state.state < GAMEPAD_BUTTON_LAST)
        {
            return isGamepadButtonPressed(jid, state.state);
        }

        return isKeyPressed(state.state);
    }
#endif

    inline bool isStatePressed(const RemapState& state)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        if (!areModsPressed(state)) return false;

        if (state.state <= MOUSE_BUTTON_LAST)
        {
            return isMouseButtonPressed(state.state);
        }

        else if (state.state < GAMEPAD_BUTTON_LAST)
        {
            return isGamepadButtonPressed(state.state);
        }

        return isKeyPressed(state.state);
#else
        return false;
#endif
    }

#undef CHECK_MOD
#undef CHECK_MOD1
}
