#pragma once

#include "Internal/Window/Backends/GLFW.h"

#include "math/utility/defines.h"

#include <string_view>

namespace GLEEC::Internal::Window::glfw
{
    using Monitor = GLFWmonitor*;

    inline math::ivec2 getMonitorPos(Monitor monitor)
    {
        math::ivec2 temp = {};
        glfwGetMonitorPos(monitor, &temp.x, &temp.y);
        return temp;
    }

    inline math::ivec4 getMonitorWorkarea(Monitor monitor)
    {
        math::ivec4 temp = {};
        glfwGetMonitorWorkarea(monitor, &temp.x, &temp.y, &temp.z, &temp.w);
        return temp;
    }

    inline math::ivec2 getMonitorPhysicalSize(Monitor monitor)
    {
        math::ivec2 temp = {};
        glfwGetMonitorPhysicalSize(monitor, &temp.x, &temp.y);
        return temp;
    }

    inline math::fvec2 getMonitorContentScale(Monitor monitor)
    {
        math::fvec2 temp = {};
        glfwGetMonitorContentScale(monitor, &temp.x, &temp.y);
        return temp;
    }

    inline std::string_view getMonitorName(Monitor monitor)
    {
        const char* name = nullptr;
        name = glfwGetMonitorName(monitor);

        return name == nullptr ?
            "Unknown Monitor Name (Error Occured)" : name;
    }

    inline void setMonitorUserPointer(Monitor monitor, void* pointer)
    {
        glfwSetMonitorUserPointer(monitor, pointer);
    }

    inline void* getMonitorUserPointer(Monitor monitor)
    {
        return glfwGetMonitorUserPointer(monitor);
    }
}
