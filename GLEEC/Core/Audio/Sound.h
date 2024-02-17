#pragma once

#include "Internal/Audio/Backend.h"

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
#include "Internal/Audio/OpenAL/Sound.h"
#else
#error "Unknown Audio backend for GLEEC!"
#endif

namespace GLEEC::Audio
{
    struct Sound
    {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Internal::Audio::OpenAL::Sound internalSound = {};
#endif

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Sound()
        {
            internalSound = Internal::Audio::OpenAL::createSound();
        }

        ~Sound()
        {
            if (alIsBuffer(internalSound))
            {
                Internal::Audio::OpenAL::destroySound(internalSound);
            }
        }
#endif
    };
}
