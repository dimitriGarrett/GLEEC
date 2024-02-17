#pragma once

#include "Internal/Audio/Backend.h"

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
#include "Internal/Audio/OpenAL/Listener.h"
#else
#error "Unknown Audio backend for GLEEC!"
#endif

namespace GLEEC::Audio
{
    struct Ears
    {
        static void pos(const math::vec3& position)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::setListenerPosition(position);
#endif
        }

        static math::vec3 pos()
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            return Internal::Audio::OpenAL::getListenerPosition();
#else
            return {};
#endif
        }

        static void vel(const math::vec3& velocity)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::setListenerVelocity(velocity);
#endif
        }

        static math::vec3 vel()
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            return Internal::Audio::OpenAL::getListenerVelocity();
#else
            return {};
#endif
        }

        static void front(const math::vec3& dir)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            math::vec<6, float> orientation;
            CHECK_AL(alGetListenerfv, AL_ORIENTATION, &orientation[0]);

            Internal::Audio::OpenAL::setListenerOrientation(dir, { orientation[3], orientation[4], orientation[5] });
#endif
        }

        static math::vec3 front()
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            const math::vec<6, float> orientation = Internal::Audio::OpenAL::getListenerOrientation();

            return { orientation[0], orientation[1], orientation[2] };
#endif
        }

        static void up(const math::vec3& uppies)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            math::vec<6, float> orientation;
            CHECK_AL(alGetListenerfv, AL_ORIENTATION, &orientation[0]);

            Internal::Audio::OpenAL::setListenerOrientation({ orientation[0], orientation[1], orientation[2] }, uppies);
#endif
        }

        static math::vec3 up()
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            const math::vec<6, float> orientation = Internal::Audio::OpenAL::getListenerOrientation();

            return { orientation[3], orientation[4], orientation[5] };
#endif
        }
    };
}
