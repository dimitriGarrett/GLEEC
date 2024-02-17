#pragma once

#include "VideoMode.h"

namespace GLEEC::Internal::Window::glfw
{
    inline Monitor getPrimaryMonitor()
    {
        return glfwGetPrimaryMonitor();
    }

    inline math::ivec2 getPrimaryMonitorPos()
    {
        return getMonitorPos(getPrimaryMonitor());
    }

    inline math::ivec4 getPrimaryMonitorWorkarea()
    {
        return getMonitorWorkarea(getPrimaryMonitor());
    }

    inline math::ivec2 getPrimaryMonitorPhysicalSize()
    {
        return getMonitorPhysicalSize(getPrimaryMonitor());
    }

    inline math::fvec2 getPrimaryMonitorContentScale()
    {
        return getMonitorContentScale(getPrimaryMonitor());
    }

    inline std::string_view getPrimaryMonitorName()
    {
        return getMonitorName(getPrimaryMonitor());
    }

    inline void setPrimaryMonitorUserPointer(void* pointer)
    {
        setMonitorUserPointer(getPrimaryMonitor(), pointer);
    }

    inline void* getPrimaryMonitorUserPointer()
    {
        return getMonitorUserPointer(getPrimaryMonitor());
    }

    inline std::vector<MonitorVideoMode> getPrimaryMonitorVideoModes()
    {
        return getMonitorVideoModes(getPrimaryMonitor());
    }

    inline MonitorVideoMode getPrimaryMonitorVideoMode()
    {
        return getMonitorVideoMode(getPrimaryMonitor());
    }

    inline void setPrimaryMonitorGamma(float gamma)
    {
        setMonitorGamma(getPrimaryMonitor(), gamma);
    }

    inline void resetPrimaryMonitorGamma()
    {
        resetMonitorGamma(getPrimaryMonitor());
    }

    inline MonitorGammaRamp getPrimaryMonitorGammaRamp()
    {
        return getMonitorGammaRamp(getPrimaryMonitor());
    }

    inline void setMonitorGammaRamp(MonitorGammaRamp ramp)
    {
        setMonitorGammaRamp(getPrimaryMonitor(), ramp);
    }
}
