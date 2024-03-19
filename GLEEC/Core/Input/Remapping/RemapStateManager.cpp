#include "RemapStateManager.h"
#include "Core/Input/JoystickManager.h"

#include "Core/Window/WindowManager.h"
#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Keyboard.h"
#include "Internal/Input/GLFW/Joystick.h"
#include "Internal/Input/GLFW/Mouse.h"
#endif

namespace GLEEC::Input
{
    inline bool RemapStateManager::stateDown(Joystick joystick,
        const RemapState& state)
    {
        if (!modsDown(state)) return false;

        if (state.state <= MOUSE_BUTTON_LAST)
        {
            return mouseDown(state.state);
        }

        else if (state.state <= GAMEPAD_BUTTON_LAST)
        {
            return gamepadDown(joystick, state.state);
        }

        return keyDown(state.state);
    }

    inline bool RemapStateManager::stateDown(const RemapState& state)
    {
        if (!modsDown(state)) return false;

        if (state.state <= MOUSE_BUTTON_LAST)
        {
            return mouseDown(state.state);
        }

        else if (state.state <= GAMEPAD_BUTTON_LAST)
        {
            return gamepadDown(state.state);
        }

        return keyDown(state.state);
    }

#define CHECK_MOD(mod, a, b)\
    ((mod & state.mods) ? keyDown(a) || keyDown(b) : true)

#define CHECK_MOD1(mod, a)\
    ((mod & state.mods) ? keyDown(a) : true)
    
    inline bool RemapStateManager::modsDown(const RemapState& state)
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

    inline bool RemapStateManager::keyDown(Key key)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return key != -1 && Internal::Input::glfw::getKey(
            Window::WindowManager::activeWindow().internalWindow, key);
#endif
    }

    inline bool RemapStateManager::mouseDown(Button mouse)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return mouse != -1 && Internal::Input::glfw::getMouseButton(
            Window::WindowManager::activeWindow().internalWindow, mouse);
#endif
    }

    inline bool RemapStateManager::gamepadDown(Joystick joystick, Button button)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return button != -1 && button <= GAMEPAD_BUTTON_LAST &&
            Internal::Input::glfw::getGamepadButtons(joystick)[
                toGLFWGamepadButton(button)];
#endif
    }

    inline bool RemapStateManager::gamepadDown(Button button)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        for (int i = 0; i < 16; ++i)
        {
            if (JoystickManager::joystickExists(i) && gamepadDown(i, button))
            {
                return true;
            }
        }
#endif

        return false;
    }
}
