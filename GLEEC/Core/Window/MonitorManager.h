#pragma once

#include "Monitor.h"

namespace GLEEC::Window
{
    struct MonitorManager
    {
        static Monitor& primaryMonitor()
        {
            // ensured by glfw to have primary first,
            // but if there is another possible backend used
            // it could change and this might be a TODO
            return monitors.front();
        }

        GLEEC_API static std::vector<Monitor> enumerateMonitors();

        static void printMonitorNames()
        {
            for (const Monitor& monitor : monitors)
            {
                LOG_INFO("Monitor currently connected: {}", monitor.name());
            }
        }

        static void init()
        {
            monitors = enumerateMonitors();

            printMonitorNames();
        }

        GLEEC_API static std::vector<Monitor> monitors;
    };
}
