#include "MonitorManager.h"

namespace GLEEC::Window
{
    std::vector<Monitor> MonitorManager::enumerateMonitors()
    {
#if GLEEC_WINDOW_BACKEND == WINDOW_BACKEND_GLFW
        std::vector<Internal::Window::glfw::Monitor> monitors = Internal::Window::glfw::enumerateMonitors();

        std::vector<Monitor> ret(monitors.size());
        for (size_t i = 0; i < monitors.size(); ++i)
        {
            ret[i] = { monitors[i] };
        }

        return ret;
#else
        return {};
#endif
    }

    std::vector<Monitor> MonitorManager::monitors = {};
}
