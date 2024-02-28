#pragma once

#include "Config/Export.h"
#include "Joystick.h"

#include "Core/Event/Event.h"

namespace GLEEC::Input
{
    struct JoystickManager
    {
        // for GLFW the id is just the jid
        static Joystick findJoystick(int id)
        {
            if (joystickPresent(id))
            {
                return joysticks.at(id);
            }

            return {};
        }

        static bool joystickPresent(int id)
        {
            return joysticks.size() > id;
        }

        static void init()
        {
            Event::addListener<Event::JoystickConnected>(+[](Joystick j)
            {
                joysticks.push_back(j);
            }, -1);

            Event::addListener<Event::JoystickDisconnected>(+[](Joystick j)
            {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
                joysticks.erase(joysticks.begin() + j.internalJoystick);
#else
                for (size_t i = 0; i < joysticks.size(); ++i)
                {
                    if (joysticks.at(i) == j)
                    {
                        joysticks.erase(joysticks.begin() + i);
                        
                        return;
                    }
                }
#endif
            }, -1);
        }

        GLEEC_API static std::vector<Joystick> joysticks;
    };
}
