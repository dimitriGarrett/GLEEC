#pragma once

#include "Internal/Audio/Backend.h"

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
#include "Internal/Audio/OpenAL/Context.h"
#else
#error "Unknown Audio backend for GLEEC!"
#endif

namespace GLEEC::Audio
{
    struct Device
    {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Internal::Audio::OpenAL::Device internalDevice = {};

        Internal::Audio::OpenAL::Context internalContext = {};
#endif

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Device(decltype(nullptr))
            : internalDevice(Internal::Audio::OpenAL::openAudioDevice(nullptr)),
            internalContext(Internal::Audio::OpenAL::createAudioContext(internalDevice))
        {
        }

        Device()
            : Device(nullptr)
        {
        }

        Device(std::string_view name)
            : internalDevice(Internal::Audio::OpenAL::openAudioDevice(name)),
            internalContext(Internal::Audio::OpenAL::createAudioContext(internalDevice))
        {
        }

        ~Device()
        {
            if (Internal::Audio::OpenAL::getCurrentContext() == internalContext)
            {
                Internal::Audio::OpenAL::makeAudioContextCurrent(nullptr);
            }

            Internal::Audio::OpenAL::destroyAudioContext(internalContext);
            Internal::Audio::OpenAL::closeAudioDevice(internalDevice);
        }
#endif
    };
}
