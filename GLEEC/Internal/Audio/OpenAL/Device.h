#pragma once

#include "Error.h"

#include <string_view>
#include <string>
#include <vector>

#include "Config/Export.h"

namespace GLEEC::Internal::Audio::OpenAL
{
    using Device = ALCdevice*;

    inline void closeAudioDevice(Device device)
    {
        CHECK_ALC(alcCloseDevice, device, device);
    }

    inline Device openAudioDevice(std::string_view name)
    {
        return alcOpenDevice(name.data());
    }

    inline Device openAudioDevice(decltype(nullptr))
    {
        return alcOpenDevice(nullptr);
    }

    inline Device defaultAudioDevice()
    {
        return alcOpenDevice(nullptr);
    }

    inline std::string defaultAudioDeviceName()
    {
        // not sure about the lifetime of the returned string by OpenAL
        return { alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER) };
    }

    inline Device preferredAudioDevice()
    {
        return defaultAudioDevice();
    }

    inline std::string preferredAudioDevicaName()
    {
        return defaultAudioDeviceName();
    }

    inline std::vector<std::string> enumerateAudioDevices()
    {
        // source: https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
        // side note: it is frustrating how well this is coded on the website
        // (i find myself constantly looking at it instead of doing it myself >()

        if (!alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
        {
            LOG_WARNING("OpenAL: device enumeration extension is not present!");

            return std::vector<std::string>{ "Unknown Default Device!" };
        }

        const ALCchar* devices;
        devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);

        if (devices == nullptr)
        {
            return { defaultAudioDeviceName() };
        }

        std::vector<std::string> names = {};

        const char* d = devices;

        do
        {
            names.push_back(std::string(d));
            d += names.back().size() + 1;
        } while (d[0] != '\0');

        return names;
    }

    inline bool audioDeviceExists(std::string_view name)
    {
        for (const std::string& device : enumerateAudioDevices())
        {
            if (device == name) return true;
        }

        return false;
    }
}
