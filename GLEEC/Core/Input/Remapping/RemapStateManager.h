#pragma once

#include "RemapState.h"

#include "Core/Input/Joystick.h"
#include "Core/Input/Key.h"
#include "Core/Input/Button.h"

#include "Config/Export.h"

namespace GLEEC::Input
{
    struct RemapStateManager
    {
        GLEEC_API static bool stateDown(Joystick joystick,
            const RemapState& state);

        GLEEC_API static bool stateDown(const RemapState& state);

    private:
        GLEEC_API static bool modsDown(const RemapState& state);

        GLEEC_API static bool keyDown(Key key);
        GLEEC_API static bool mouseDown(Button mouse);
        GLEEC_API static bool gamepadDown(Joystick joystick, Button button);
        GLEEC_API static bool gamepadDown(Button button);
    };
}
