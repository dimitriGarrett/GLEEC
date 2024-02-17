#pragma once

#include "VideoMode.h"

namespace GLEEC::Internal::Window::glfw
{
    struct MonitorGammaRamp
    {
        std::vector<unsigned short> red = {};
        std::vector<unsigned short> green = {};
        std::vector<unsigned short> blue = {};

        size_t size() const
        {
            return red.size(); // they all have the same size
        }
    };

    inline void setMonitorGamma(Monitor monitor, float gamma)
    {
        glfwSetGamma(monitor, gamma);
    }

    inline void resetMonitorGamma(Monitor monitor)
    {
        setMonitorGamma(monitor, 1.0f);
    }

    inline MonitorGammaRamp getMonitorGammaRamp(Monitor monitor)
    {
        MonitorGammaRamp ramp = {};

        const GLFWgammaramp* internalGammaRamp = glfwGetGammaRamp(monitor);

        if (internalGammaRamp == nullptr)
        {
            LOG_ERROR("Monitor: {} failed to get gamma ramp!", static_cast<void*>(monitor));

            return ramp;
        }

        size_t s = internalGammaRamp->size;
        ramp.red = std::vector<unsigned short>(internalGammaRamp->red, internalGammaRamp->red + s);
        ramp.green = std::vector<unsigned short>(internalGammaRamp->green, internalGammaRamp->green + s);
        ramp.blue = std::vector<unsigned short>(internalGammaRamp->blue, internalGammaRamp->blue + s);

        return ramp;
    }

    inline void setMonitorGammaRamp(Monitor monitor, MonitorGammaRamp& ramp)
    {
        const GLFWgammaramp internalGammaRamp =
        {
            .red = ramp.red.data(),
            .green = ramp.green.data(),
            .blue = ramp.blue.data(),

            .size = static_cast<unsigned int>(ramp.red.size()),
        };

        glfwSetGammaRamp(monitor, &internalGammaRamp);
    }

}
