#pragma once

#include "Key.h"

namespace GLEEC::Input
{
    using Button = uint32_t;

    // not the same as GLFW!
    inline constexpr Button MOUSE_BUTTON_1 = 0;
    inline constexpr Button MOUSE_BUTTON_2 = 1;
    inline constexpr Button MOUSE_BUTTON_3 = 2;
    inline constexpr Button MOUSE_BUTTON_4 = 3;
    inline constexpr Button MOUSE_BUTTON_5 = 4;
    inline constexpr Button MOUSE_BUTTON_6 = 5;
    inline constexpr Button MOUSE_BUTTON_7 = 6;
    inline constexpr Button MOUSE_BUTTON_8 = 7;

    inline constexpr Button GAMEPAD_BUTTON_A = 8;
    inline constexpr Button GAMEPAD_BUTTON_B = 9;
    inline constexpr Button GAMEPAD_BUTTON_X = 10;
    inline constexpr Button GAMEPAD_BUTTON_Y = 11;
    inline constexpr Button GAMEPAD_BUTTON_LEFT_BUMPER = 12;
    inline constexpr Button GAMEPAD_BUTTON_RIGHT_BUMPER = 13;
    inline constexpr Button GAMEPAD_BUTTON_BACK = 14;
    inline constexpr Button GAMEPAD_BUTTON_START = 15;
    inline constexpr Button GAMEPAD_BUTTON_GUIDE = 16;
    inline constexpr Button GAMEPAD_BUTTON_LEFT_THUMB = 17;
    inline constexpr Button GAMEPAD_BUTTON_RIGHT_THUMB = 18;
    inline constexpr Button GAMEPAD_BUTTON_DPAD_UP = 19;
    inline constexpr Button GAMEPAD_BUTTON_DPAD_RIGHT = 20;
    inline constexpr Button GAMEPAD_BUTTON_DPAD_DOWN = 21;
    inline constexpr Button GAMEPAD_BUTTON_DPAD_LEFT = 22;

    inline constexpr Button MOUSE_BUTTON_LAST =      MOUSE_BUTTON_8;
    inline constexpr Button MOUSE_BUTTON_LEFT =      MOUSE_BUTTON_1;
    inline constexpr Button MOUSE_BUTTON_RIGHT =     MOUSE_BUTTON_2;
    inline constexpr Button MOUSE_BUTTON_MIDDLE =    MOUSE_BUTTON_3;

    inline constexpr Key NUM_MOUSE_BUTTONS = MOUSE_BUTTON_LAST;

    inline constexpr Button GAMEPAD_BUTTON_LAST =   GAMEPAD_BUTTON_DPAD_LEFT;
    inline constexpr Button GAMEPAD_BUTTON_CROSS =   GAMEPAD_BUTTON_A;
    inline constexpr Button GAMEPAD_BUTTON_CIRCLE =   GAMEPAD_BUTTON_B;
    inline constexpr Button GAMEPAD_BUTTON_SQUARE =   GAMEPAD_BUTTON_X;
    inline constexpr Button GAMEPAD_BUTTON_TRIANGLE =   GAMEPAD_BUTTON_Y;

    inline constexpr Key NUM_GAMEPAD_BUTTONS = GAMEPAD_BUTTON_LAST -
        (MOUSE_BUTTON_LAST + 1);

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
    inline constexpr Button toGLFWMouseButton(Button button)
    {
        return button - MOUSE_BUTTON_1;
    }

    inline constexpr Button toGLFWGamepadButton(Button button)
    {
        return button - GAMEPAD_BUTTON_A;
    }
#endif
}
