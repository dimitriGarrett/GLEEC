#pragma once

#include "Core/Input/Button.h"
#include "Core/Input/Joystick.h"
#include "Core/Input/Key.h"

#include "Config/Export.h"

#include <bitset>

namespace GLEEC::Input
{
    /*
       ...Pressed should be avoided if possible, because you can miss inputs
       if the user was fast enough. Instead, prefer the callbacks using
       the event system in core (same goes for ...Released functions)
    */

    struct InputManager
    {
        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void update();

        GLEEC_API static bool keyDown(Key key);
        GLEEC_API static bool mouseDown(Button button);
        GLEEC_API static bool gamepadDown(Joystick joystick, Button button);

        GLEEC_API static bool keyPressed(Key key);
        GLEEC_API static bool mousePressed(Button button);
        GLEEC_API static bool gamepadPressed(Joystick joystick, Button button);

        GLEEC_API static bool keyUp(Key key);
        GLEEC_API static bool mouseUp(Button button);
        GLEEC_API static bool gamepadUp(Joystick joystick, Button button);

        GLEEC_API static bool keyReleased(Key key);
        GLEEC_API static bool mouseReleased(Button button);
        GLEEC_API static bool gamepadReleased(Joystick joystick, Button button);

        GLEEC_API static float gamepadAxis(Joystick joystick, size_t axis);

        GLEEC_API static std::bitset<NUM_KEYS> polledKeyStates;
        GLEEC_API static std::bitset<NUM_MOUSE_BUTTONS> polledMouseStates;
        GLEEC_API static std::bitset<NUM_GAMEPAD_BUTTONS> polledButtonStates;
    };
}
