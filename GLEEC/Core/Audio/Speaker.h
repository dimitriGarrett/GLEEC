#pragma once

#include "Internal/Audio/Backend.h"

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
#include "Internal/Audio/OpenAL/Speaker.h"
#else
#error "Unknown Audio backend for GLEEC!"
#endif

#include "Sound.h"

namespace GLEEC::Audio
{
    struct Speaker
    {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Internal::Audio::OpenAL::Speaker internalSpeaker = {};
#endif

        void pos(const math::vec3& position)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::setSpeakerPosition(internalSpeaker, position);
#endif
        }

        math::vec3 pos() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            return Internal::Audio::OpenAL::getSpeakerPosition(internalSpeaker);
#else
            return {};
#endif
        }

        void vel(const math::vec3& velocity)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::setSpeakerVelocity(internalSpeaker, velocity);
#endif
        }

        math::vec3 vel() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            return Internal::Audio::OpenAL::getSpeakerVelocity(internalSpeaker);
#else
            return {};
#endif
        }

        void dir(const math::vec3& direction)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::setSpeakerDirection(internalSpeaker, direction);
#endif
        }

        math::vec3 dir() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            return Internal::Audio::OpenAL::getSpeakerDirection(internalSpeaker);
#else
            return {};
#endif
        }

        void loop(bool yesno)
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::setSpeakerLooping(internalSpeaker, yesno);
#endif
        }

        void startLooping()
        {
            loop(true);
        }

        void stopLooping()
        {
            loop(false);
        }

        bool isLooping() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            return Internal::Audio::OpenAL::getSpeakerLooping(internalSpeaker);
#else
            return false;
#endif
        }

        void play() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::playSpeaker(internalSpeaker);
#endif
        }

        void pause() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::pauseSpeaker(internalSpeaker);
#endif
        }

        void stop() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::stopSpeaker(internalSpeaker);
#endif
        }

        void rewind() const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::rewindSpeaker(internalSpeaker);
#endif
        }

        void queueSound(Sound& sound) const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::queueSpeakerSound(internalSpeaker, sound.internalSound);
#endif
        }

        void unqueueSound(Sound& sound) const
        {
#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
            Internal::Audio::OpenAL::unqueueSpeakerSound(internalSpeaker, sound.internalSound);
#endif
        }

#if GLEEC_AUDIO_BACKEND == AUDIO_BACKEND_OPENAL
        Speaker()
        {
            internalSpeaker = Internal::Audio::OpenAL::createSpeaker();
        }

        Speaker(Sound& sound)
        {
            internalSpeaker = Internal::Audio::OpenAL::createSpeaker();
            Internal::Audio::OpenAL::queueSpeakerSound(internalSpeaker, sound.internalSound);
        }

        ~Speaker()
        {
            // if it hasn't been destroyed already
            if (alIsSource(internalSpeaker))
            {
                Internal::Audio::OpenAL::stopSpeaker(internalSpeaker);
                Internal::Audio::OpenAL::setSpeakerSound(internalSpeaker, nullptr);
                Internal::Audio::OpenAL::destroySpeaker(internalSpeaker);
            }
        }
#endif
    };
}
