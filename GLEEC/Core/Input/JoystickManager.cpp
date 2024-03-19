#include "JoystickManager.h"

#include "Core/Event/Event.h"

#include "Internal/Input/Backend.h"

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
#include "Internal/Input/GLFW/Joystick.h"
#endif

namespace GLEEC::Input
{
    std::vector<Joystick> JoystickManager::joysticks = {};

    inline void JoystickManager::init()
    {
        Event::addListener<Event::JoystickConnected>(+[](Joystick j)
        {
            joysticks.push_back(j);
        }, -1);

        Event::addListener<Event::JoystickDisconnected>(+[](Joystick j)
        {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
            joysticks.erase(joysticks.begin() + j);
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

    inline bool JoystickManager::joystickExists(Joystick joystick)
    {
        return joystick < joysticks.size();

/* #if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return Internal::Input::glfw::joystickPresent(joystick);
#endif */
    }

    inline std::string_view JoystickManager::joystickName(Joystick joystick)
    {
#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
        return Internal::Input::glfw::getJoystickName(joystick);
#endif
    }
}
