#pragma once

#include "Config/Export.h"
#include "Device.h"

#include <unordered_map>

namespace GLEEC::Audio
{
    struct DeviceManager
    {
        static void printDeviceNames()
        {
            for (const auto& d : potentialDevices)
            {
                LOG_INFO("Present audio device: {}", d);
            }
        }

        static void useDevice(const Device& d)
        {
// most likely this is only useful for openal,
// because it resembles OpenGL by needing a context
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::makeAudioContextCurrent(d.internalContext);
#endif
        }

        static void useDevice(std::string_view name)
        {
            useDevice(openDevices.at(key(name)));
        }

        static void useDevice(decltype(nullptr))
        {
            useDevice(openDevices.at(key()));
        }

        static Device& openDevice(std::string_view name)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            auto openedDevice =
                openDevices.try_emplace(key(), name);

            return (openedDevice.first)->second;
#else
            return openDevices[key(name)] = {};
#endif
        }

        static Device& openDevice(decltype(nullptr))
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            auto openedDevice =
                openDevices.try_emplace(key(), nullptr);

            return (openedDevice.first)->second;
#else
            return openDevices[key()] = {};
#endif
        }

        static Device& openDefaultDevice()
        {
            return openDevice(nullptr);
        }

        static void closeDevices()
        {
            openDevices.clear();
        }

        GLEEC_API static std::vector<std::string> potentialDevices;
        GLEEC_API static std::unordered_map<size_t, Device> openDevices;

    private:
        static size_t key(std::string_view name)
        {
            return std::hash<std::string_view>{}(name);
        }

        static size_t key(decltype(nullptr))
        {
            return 0;
        }

        static size_t key()
        {
            return key(nullptr);
        }
    };
}
