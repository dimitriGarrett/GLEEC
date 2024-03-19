#pragma once

#include "Joystick.h"

#include "Config/Export.h"

#include <string_view>
#include <vector>

namespace GLEEC::Input
{
    struct JoystickManager
    {
        GLEEC_API static void init();

        GLEEC_API static bool joystickExists(Joystick joystick);

        GLEEC_API static std::string_view joystickName(Joystick joystick);

        GLEEC_API static std::vector<Joystick> joysticks;
    };
}
