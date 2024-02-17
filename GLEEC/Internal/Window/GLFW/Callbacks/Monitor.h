#pragma once

#include "Internal/Window/GLFW/Monitor/Monitor.h"

#include "Internal/Event/Subway.h"
#include "Internal/Window/Events.h"

#include "Internal/Log/EnableInternalLogging"

#if GLEEC_ALL_INTERNAL_LOGGING
#include "Internal/Log/Log.h"
#endif

namespace GLEEC::Internal::Window::glfw
{
    using InternalMonitorCallback = void(*)(GLFWmonitor*, int);

    // TODO: uncomment event stuff
    inline void setMonitorCallback()
    {
        glfwSetMonitorCallback([](GLFWmonitor* m, int event)
        {
            if (event == GLFW_CONNECTED)
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Monitor: {}): \"{}\" connected!", static_cast<void*>(m), getMonitorName(m));
#endif
                Event::fireEvent<Events::MonitorConnectedEvent>(Monitor{ m });
            }

            else
            {
#if GLEEC_ALL_INTERNAL_LOGGING
                LOG_INFO("(Monitor: {}): \"{}\" disconnected!", static_cast<void*>(m), getMonitorName(m));
#endif
                Event::fireEvent<Events::MonitorDisconnectedEvent>(Monitor{ m });
            }
        });
    }
}
