#pragma once

#include "SoundManager.h"
#include "DeviceManager.h"
#include "SpeakerManager.h"

#include "Internal/Audio/Backend.h"

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
#include "Internal/Audio/OpenAL/Init.h"
#else
#error "Unknown Audio backend for GLEEC!"
#endif

namespace GLEEC::Audio
{
    inline void init(const Device& device)
    {
        DeviceManager::useDevice(device);

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Internal::Audio::OpenAL::init(device.internalContext);
#endif

        DeviceManager::printDeviceNames();
    }

    inline void init(std::string_view deviceName)
    {
        init(DeviceManager::openDevice(deviceName));

        LOG_INFO("Chosen audio device: {}", deviceName);
    }

    inline void init(decltype(nullptr))
    {
        init(DeviceManager::openDevice(nullptr));

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        LOG_INFO("Chosen audio device: {}", Internal::Audio::OpenAL::defaultAudioDeviceName());
#else
        LOG_INFO("Chosen audio device: default");
#endif
    }

    inline void init()
    {
        init(nullptr);
    }

    inline void destroy()
    {
        SpeakerManager::destroySpeakers();
        SoundManager::destroySounds();
        DeviceManager::closeDevices();
    }
}
