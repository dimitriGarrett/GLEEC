#pragma once

#include "Internal/Input/Backends/GLFW.h"

#include <string_view>

namespace GLEEC::Internal::Input::glfw
{
    inline void setClipboardString(std::string_view data)
    {
        glfwSetClipboardString(nullptr, data.data());
    }

    inline std::string_view getClipboardString()
    {
        const char* data = glfwGetClipboardString(nullptr);
        return data == nullptr ? "" : data;
    }
}
