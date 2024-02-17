#pragma once

#include "Internal/Audio/Backends/OpenAL.h"
#include "Internal/Log/Log.h"

#include <type_traits>

namespace GLEEC::Internal::Audio::OpenAL
{
    inline ALenum getALError()
    {
        return alGetError();
    }

    inline ALCenum getALCError(ALCdevice* device = nullptr)
    {
        return alcGetError(device);
    }

    inline std::string getALErrorString(ALenum error)
    {
        switch (error)
        {
        case AL_NO_ERROR: return "OpenAL Error (AL): no error!";
        case AL_INVALID_NAME: return "OpenAL Error (AL): invalid name!";
        case AL_INVALID_ENUM: return "OpenAL Error (AL): invalid enum!";
        case AL_INVALID_VALUE: return "OpenAL Error (AL): invalid value!";
        case AL_INVALID_OPERATION: return "OpenAL Error (AL): invalid operation!";
        case AL_OUT_OF_MEMORY: return "OpenAL Error (AL): something really went wrong (no memory!)";
        default: return "OpenAL Error: (AL): unknown error!";
        }
    }

    inline std::string getALErrorString()
    {
        return getALErrorString(getALError());
    }

    inline std::string getALCErrorString(ALCenum error)
    {
        switch (error)
        {
        case ALC_NO_ERROR: return "OpenAL Error (ALC): no error!";
        case ALC_INVALID_VALUE: return "OpenAL Error (ALC): invalid value!";
        case ALC_INVALID_DEVICE: return "OpenAL Error (ALC): invalid device!";
        case ALC_INVALID_CONTEXT: return "OpenAL Error (ALC): invalid context!";
        case ALC_INVALID_ENUM: return "OpenAL Error (ALC): invalid enum!";
        case ALC_OUT_OF_MEMORY: return "OpenAL Error (ALC): something really went wrong (no memory!)";
        default: return "OpenAL Error: (ALC): unknown error!";
        }
    }

    inline std::string getALCErrorString(ALCdevice* device = nullptr)
    {
        return getALCErrorString(getALCError(device));
    }

    namespace detail
    {
        template <typename F, typename... Args>
        void checkAL(const char* file, int line, F fun, Args&&... args)
            requires (std::is_same_v<decltype(fun(args...)), void>)
        {
            fun(std::forward<Args>(args)...);

            ALenum error = getALError();
            if (error != AL_NO_ERROR)
            {
                LOG_WARNING("{} at: {}: {}", getALErrorString(error), file, line);
            }
        }

        template <typename F, typename... Args>
        auto checkAL(const char* file, int line, F fun, Args&&... args)
            requires (!std::is_same_v<decltype(fun(args...)), void>)
        {
            auto r = fun(std::forward<Args>(args)...);

            ALenum error = getALError();
            if (error != AL_NO_ERROR)
            {
                LOG_WARNING("{} at: {}: {}", getALErrorString(error), file, line);
            }
            return r;
        }

        template <typename F, typename... Args>
        void checkALC(const char* file, int line, F fun, ALCdevice* device, Args&&... args)
            requires (std::is_same_v<decltype(fun(args...)), void>)
        {
            fun(std::forward<Args>(args)...);

            ALCenum error = getALCError(device);
            if (error != ALC_NO_ERROR)
            {
                LOG_WARNING("{} at: {}: {}", getALCErrorString(error), file, line);
            }
        }

        template <typename F, typename... Args>
        auto checkALC(const char* file, int line, F fun, ALCdevice* device, Args&&... args)
            requires (!std::is_same_v<decltype(fun(args...)), void>)
        {
            auto r = fun(std::forward<Args>(args)...);

            ALCenum error = getALCError(device);
            if (error != ALC_NO_ERROR)
            {
                LOG_WARNING("{} at: {}: {}", getALCErrorString(error), file, line);
            }
            return r;
        }
    }
}

#define CHECK_AL(fun, ...) ::GLEEC::Internal::Audio::OpenAL::detail::checkAL(__FILE__, __LINE__, fun, ##__VA_ARGS__)
#define CHECK_ALC(fun, device, ...) ::GLEEC::Internal::Audio::OpenAL::detail::checkALC(__FILE__, __LINE__, fun, device, ##__VA_ARGS__)
// just to round up to 100 :)
