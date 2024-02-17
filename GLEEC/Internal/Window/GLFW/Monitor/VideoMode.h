#pragma once

#include "Internal/Log/Log.h"
#include "Monitor.h"

#include <vector>

namespace GLEEC::Internal::Window::glfw
{
    using MonitorVideoMode = GLFWvidmode;

    inline std::vector<MonitorVideoMode> getMonitorVideoModes(Monitor monitor)
    {
        int c = 0;
        const MonitorVideoMode* internalVideoModes = glfwGetVideoModes(monitor, &c);

        if (c == 0 || internalVideoModes == nullptr)
        {
            LOG_ERROR("Monitor {}: failed to get video modes!", static_cast<void*>(monitor));

            return {};
        }

        return std::vector<MonitorVideoMode>(internalVideoModes, internalVideoModes + c);
    }

    inline MonitorVideoMode getMonitorVideoMode(Monitor monitor)
    {
        const GLFWvidmode* internalVideoMode = glfwGetVideoMode(monitor);

        if (internalVideoMode == nullptr)
        {
            LOG_ERROR("Monitor: {}: failed to get video mode!", static_cast<void*>(monitor));

            return {};
        }

        return *internalVideoMode;
    }
}
