#pragma once

#include "Internal/Log/Log.h"
#include "Monitor.h"

#include <vector>

namespace GLEEC::Internal::Window::glfw
{
    inline std::vector<Monitor> enumerateMonitors()
    {
        int c = 0;
        Monitor* monitors = glfwGetMonitors(&c);

        // if there are no monitors for any reason an error occured
        if (c == 0 || monitors == nullptr)
        {
            LOG_ERROR("Monitor: no monitors found!");

            return {};
        }

        return std::vector<Monitor>(monitors, monitors + c);
    }
}
