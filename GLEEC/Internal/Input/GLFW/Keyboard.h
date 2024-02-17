#pragma once

#include "Codes/Key.h"
#include "Internal/Window/Window.h"

namespace GLEEC::Internal::Input::glfw
{
    inline std::string_view getKeyName(int32_t key, int32_t scancode)
    {
        const char* internalKeyName = glfwGetKeyName(key, scancode);
        return internalKeyName == nullptr ? "Unknown Key!" : internalKeyName;
    }

    inline int32_t getKeyScancode(int32_t key)
    {
        return glfwGetKeyScancode(key);
    }

    inline std::string_view getKeyName(int32_t key)
    {
        return key != KEY_UNKNOWN ? getKeyName(key, 0) : "Unknown Key!";
    }

    inline bool getKey(Window::glfw::Window window, int32_t key)
    {
        return glfwGetKey(window, key);
    }
}
