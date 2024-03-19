#pragma once

#include "Internal/Input/Backends/GLFW.h"

#include <string_view>
#include <vector>
#include <array>

namespace GLEEC::Internal::Input::glfw
{
    using Joystick = int;

    using GamepadButtons = std::array<unsigned char, 15>;
    using GamepadAxes = std::array<float, 6>;

    struct GamepadState
    {
        GamepadButtons buttons = { 0 };
        GamepadAxes axes = { 0.0f };
    };

    // I was just down down bad
    inline bool joystickPresent(Joystick jid)
    {
        return glfwJoystickPresent(jid);
    }

    inline std::vector<float> getJoystickAxes(Joystick jid)
    {
        int c = 0;
        const float* internalAxes = glfwGetJoystickAxes(jid, &c);

        return std::vector<float>(internalAxes, internalAxes + c);
    }

    inline std::vector<unsigned char> getJoystickButtons(Joystick jid)
    {
        int c = 0;
        const unsigned char* internalButtons = glfwGetJoystickButtons(jid, &c);

        return std::vector<unsigned char>(internalButtons, internalButtons + c);
    }

    inline std::vector<unsigned char> getJoystickHats(Joystick jid)
    {
        int c = 0;
        const unsigned char* internalHats = glfwGetJoystickHats(jid, &c);

        return std::vector<unsigned char>(internalHats, internalHats + c);
    }

    inline std::string_view getJoystickName(Joystick jid)
    {
        const char* name = glfwGetJoystickName(jid);
        return name == nullptr ? "Unkown Joystick Name!" : name;
    }

    inline std::string_view getJoystickGUID(Joystick jid)
    {
        const char* guid = glfwGetJoystickGUID(jid);
        return guid == nullptr ? "Unknown GUID!" : guid;
    }

    inline void setJoystickUserPointer(Joystick jid, void* data)
    {
        glfwSetJoystickUserPointer(jid, data);
    }

    inline void* getJoystickUserPointer(Joystick jid)
    {
        return glfwGetJoystickUserPointer(jid);
    }

    inline bool joystickIsGamepad(Joystick jid)
    {
        return glfwJoystickIsGamepad(jid);
    }

    inline bool updateGamepadMappings(std::string_view str)
    {
        return glfwUpdateGamepadMappings(str.data());
    }

    inline std::string_view getGamepadName(Joystick jid)
    {
        const char* name = glfwGetGamepadName(jid);
        return name == nullptr ? getJoystickName(jid) : name;
    }

    inline GamepadState getGamepadState(Joystick jid)
    {
        GLFWgamepadstate state = {};

        if (glfwGetGamepadState(jid, &state))
        {
            if constexpr (sizeof(GamepadState) == sizeof(GLFWgamepadstate))
            {
                return *reinterpret_cast<GamepadState*>(&state);
            }

            GamepadState temp = {};

            for (int i = 0; i < sizeof(temp.buttons) / sizeof(temp.buttons[0]); ++i)
            {
                temp.buttons[i] = state.buttons[i];
            }

            for (int i = 0; i < sizeof(temp.axes) / sizeof(temp.axes[0]); ++i)
            {
                temp.axes[i] = state.axes[i];
            }

            return temp;
        }

        return {};
    }

    inline GamepadButtons getGamepadButtons(Joystick jid)
    {
        return getGamepadState(jid).buttons;
    }

    inline GamepadAxes getGamepadAxes(Joystick jid)
    {
        return getGamepadState(jid).axes;
    }
}
