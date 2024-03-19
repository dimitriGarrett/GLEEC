#include "InputManager.h"
#include "JoystickManager.h"

#include "Remapping/RemapStateManager.h"
#include "Remapping/Remapper.h"

#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
#include "Internal/Input/GLFW/Init.h"
#endif

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Joystick.h"
#include "Internal/Input/GLFW/Update.h"
#endif

namespace GLEEC::Input
{
    std::bitset<NUM_KEYS> InputManager::polledKeyStates = {};
    std::bitset<NUM_MOUSE_BUTTONS> InputManager::polledMouseStates = {};
    std::bitset<NUM_GAMEPAD_BUTTONS> InputManager::polledButtonStates = {};

    inline void InputManager::init()
    {
#if GLEEC_INPUT_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::init();
#endif

        JoystickManager::init();
    }

    inline void InputManager::destroy()
    {
#if GLEEC_INPUT_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::terminate();
#endif
    }

    inline void InputManager::update()
    {
#if GLEEC_INPUT_BACKEND == WINDOW_BACKEND_GLFW
        Internal::Input::glfw::pollEvents();
#endif
    }

    inline bool InputManager::keyDown(Key key)
    {
        Remapper& rp = Remapper::currentPreset();

        return RemapStateManager::stateDown(rp.unmap(key));
    }

    inline bool InputManager::keyPressed(Key key)
    {
        Remapper& rp = Remapper::currentPreset();

        bool current = RemapStateManager::stateDown(rp.unmap(key));

        bool old = polledKeyStates[key];
        polledKeyStates[key] = current;

        return current && !old;
    }

    inline bool InputManager::mouseDown(Button key)
    {
        Remapper& rp = Remapper::currentPreset();

        return RemapStateManager::stateDown(rp.unmap(key));
    }

    inline bool InputManager::mousePressed(Button button)
    {
        Remapper& rp = Remapper::currentPreset();

        bool current = RemapStateManager::stateDown(rp.unmap(button));

        bool old = polledButtonStates[button];
        polledButtonStates[button] = current;

        return current && !old;
    }

    inline bool InputManager::gamepadDown(Joystick joystick, Button button)
    {
        Remapper& rp = Remapper::currentPreset();

        return RemapStateManager::stateDown(joystick, rp.unmap(button));
    }

    inline bool InputManager::gamepadPressed(Joystick joystick, Button button)
    {
        Remapper& rp = Remapper::currentPreset();

        bool current = RemapStateManager::stateDown(joystick, rp.unmap(button));

        bool old = polledButtonStates[button];
        polledButtonStates[button] = current;

        return current && !old;
    }

    inline bool InputManager::keyUp(Key key)
    {
        return !keyDown(key);
    }

    inline bool InputManager::keyReleased(Key key)
    {
        Remapper& rp = Remapper::currentPreset();

        bool current = RemapStateManager::stateDown(rp.unmap(key));

        bool old = polledKeyStates[key];
        polledKeyStates[key] = current;

        return !current && old;
    }

    inline bool InputManager::mouseUp(Button button)
    {
        return !mouseDown(button);
    }

    inline bool InputManager::mouseReleased(Button button)
    {
        Remapper& rp = Remapper::currentPreset();

        bool current = RemapStateManager::stateDown(rp.unmap(button));

        bool old = polledButtonStates[button];
        polledButtonStates[button] = current;

        return !current && old;
    }

    inline bool InputManager::gamepadUp(Joystick joystick, Button button)
    {
        return !gamepadDown(joystick, button);
    }

    inline bool InputManager::gamepadReleased(Joystick joystick, Button button)
    {
        Remapper& rp = Remapper::currentPreset();

        bool current = RemapStateManager::stateDown(joystick, rp.unmap(button));

        bool old = polledButtonStates[button];
        polledButtonStates[button] = current;

        return !current && old;
    }

    inline float InputManager::gamepadAxis(Joystick joystick, size_t axis)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return Internal::Input::glfw::getGamepadAxes(joystick)[axis];
#else
        return 0.0f;
#endif
    }
}
