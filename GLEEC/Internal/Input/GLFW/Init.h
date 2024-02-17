#pragma once

#include "Internal/Window/Monitor.h"

#include "Internal/Window/Callbacks.h"
#include "Internal/Input/Callbacks.h"

#include "Internal/Input/GLFW/Mode.h"

namespace GLEEC::Internal::Input::glfw
{
    enum class PHYSICAL_ERROR : int
    {
        NONE =                   GLFW_NO_ERROR,
        NOT_INITIALIZED =        GLFW_NOT_INITIALIZED,
        NO_CURRENT_CONTEXT =     GLFW_NO_CURRENT_CONTEXT,
        INVALID_ENUM =           GLFW_INVALID_ENUM,
        INVALID_VALUE =          GLFW_INVALID_VALUE,
        OUT_OF_MEMORY =          GLFW_OUT_OF_MEMORY,
        API_UNAVAILABLE =        GLFW_API_UNAVAILABLE,
        VERSION_UNAVAILABLE =    GLFW_VERSION_UNAVAILABLE,
        PLATFORM_ERROR =         GLFW_PLATFORM_ERROR,
        FORMAT_UNAVAILABLE =     GLFW_FORMAT_UNAVAILABLE,
        NO_WINDOW_CONTEXT =      GLFW_NO_WINDOW_CONTEXT,
    };

    struct PhysicalError
    {
        PHYSICAL_ERROR error = {};
        std::string error_desc = "";
    };

    using ErrorCallback = void(*)(int, const char*);

    inline void setErrorCallback()
    {
        glfwSetErrorCallback(+[](int errorCode, const char* desc)
        {
            LOG_ERROR("GLFW error (code: {}): \"{}\"", errorCode, desc);
        });
    }

    inline PhysicalError getErrorGLFW()
    {
        PhysicalError err;

        const char* desc = nullptr;
        err.error = static_cast<PHYSICAL_ERROR>(glfwGetError(&desc));
        err.error_desc = desc == nullptr ? "" : std::string(desc);

        return err;
    }

    struct Version
    {
        int major = {};
        int minor = {};
        int rev   = {};
    };

    inline Version version()
    {
        Version temp = {};
        glfwGetVersion(&temp.major, &temp.minor, &temp.rev);
        return temp;
    }

    inline std::string_view versionString()
    {
        return glfwGetVersionString();
    }

    inline bool init()
    {
        setErrorCallback();

        LOG_INFO("GLFW version: {}.{}.{}", version().major, version().minor, version().rev);
        LOG_INFO("GLFW version string: {}", versionString());

        bool i = glfwInit();

        if (i)
        {
            Window::glfw::setMonitorCallback();

            LOG_INFO("glfw has been initialized!");
        }

        Event::addListener<Events::WindowCreated>(+[](Window::glfw::Window window)
        {
            Window::glfw::setAllWindowCallbacks(window);
            Input::glfw::setAllCallbacks(window);

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
            Input::glfw::setInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
#endif
        });

        return i;
    }

    inline void terminate()
    {
        glfwTerminate();
    }

    inline void initHint(int hint, int value)
    {
        glfwInitHint(hint, value);
    }
}
