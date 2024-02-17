#pragma once

#include "Sound.h"

#include "math/utility/defines.h"

#include <vector>

namespace GLEEC::Internal::Audio::OpenAL
{
    using Speaker = ALuint;

    struct Orientation
    {
        math::fvec3 at = {};
        math::fvec3 up = {};
    };

    inline Speaker createSpeaker()
    {
        Speaker temp = {};
        CHECK_AL(alGenSources, 1, &temp);
        return temp;
    }

    inline void destroySpeaker(Speaker& speaker)
    {
        CHECK_AL(alDeleteBuffers, 1, &speaker);
    }

    inline void setSpeakerPitch(const Speaker& speaker, float pitch)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_PITCH,
            pitch);
    }

    inline void setSpeakerGain(const Speaker& speaker, float gain)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_GAIN,
            gain);
    }

    inline void setSpeakerMaxDistance(const Speaker& speaker, float dist)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_MAX_DISTANCE,
            dist);
    }

    inline void setSpeakerRolloffFactor(const Speaker& speaker, float factor)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_ROLLOFF_FACTOR,
            factor);
    }

    inline void setSpeakerReferenceDistance(const Speaker& speaker, float dist)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_REFERENCE_DISTANCE,
            dist);
    }

    inline void setSpeakerMinGain(const Speaker& speaker, float gain)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_MIN_GAIN,
            gain);
    }

    inline void setSpeakerMaxGain(const Speaker& speaker, float gain)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_MAX_GAIN,
            gain);
    }

    inline void setSpeakerConeOuterGain(const Speaker& speaker, float gain)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_CONE_OUTER_GAIN,
            gain);
    }

    inline void setSpeakerConeInnerAngle(const Speaker& speaker, float angle)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_CONE_OUTER_GAIN,
            angle);
    }

    inline void setSpeakerConeOuterAngle(const Speaker& speaker, float angle)
    {
        CHECK_AL(alSourcef,
            speaker,
            AL_CONE_OUTER_GAIN,
            angle);
    }

    inline void setSpeakerPosition(const Speaker& speaker, const math::fvec3& pos)
    {
        CHECK_AL(alSourcefv,
            speaker,
            AL_POSITION,
            &pos.x);
    }

    inline void setSpeakerVelocity(const Speaker& speaker, const math::fvec3& vel)
    {
        CHECK_AL(alSourcefv,
            speaker,
            AL_VELOCITY,
            &vel.x);
    }

    inline void setSpeakerDirection(const Speaker& speaker, const math::fvec3& dir)
    {
        CHECK_AL(alSourcefv,
            speaker,
            AL_DIRECTION,
            &dir.x);
    }

    inline void setSpeakerRelativeToListener(const Speaker& speaker, bool flag)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_SOURCE_RELATIVE,
            flag);
    }

    enum SpeakerState : int
    {
        STOPPED = AL_STOPPED,
        PLAYING = AL_PLAYING,
        PAUSED  = AL_PAUSED,
    };

    enum SpeakerType : int
    {
        UNDETERMINED = AL_UNDETERMINED,
        STATIC = AL_STATIC,
        STREAMING = AL_STREAMING,
    };

    inline void setSpeakerType(const Speaker& speaker, SpeakerType type)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_SOURCE_TYPE,
            static_cast<int>(type));
    }

    inline void setSpeakerLooping(const Speaker& speaker, bool flag)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_LOOPING,
            flag);
    }

    inline void setSpeakerSound(const Speaker& speaker, decltype(nullptr))
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_BUFFER,
            0);
    }

    inline void setSpeakerSound(const Speaker& speaker, const Sound& sound)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_BUFFER,
            sound);
    }

    inline void setSpeakerState(const Speaker& speaker, SpeakerState state)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_SOURCE_STATE,
            static_cast<int>(state));
    }

    inline void setSpeakerOffsetSeconds(const Speaker& speaker, int seconds)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_SEC_OFFSET,
            seconds);
    }

    inline void setSpeakerOffsetSamples(const Speaker& speaker, int samples)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_SAMPLE_OFFSET,
            samples);
    }

    inline void setSpeakerOffsetBytes(const Speaker& speaker, int bytes)
    {
        CHECK_AL(alSourcei,
            speaker,
            AL_BYTE_OFFSET,
            bytes);
    }

    inline float getSpeakerPitch(const Speaker& speaker)
    {
        float pitch = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_PITCH,
            &pitch);
        return pitch;
    }

    inline float getSpeakerGain(const Speaker& speaker)
    {
        float gain = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_GAIN,
            &gain);
        return gain;
    }

    inline float getSpeakerMaxDistance(const Speaker& speaker)
    {
        float dist = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_MAX_DISTANCE,
            &dist);
        return dist;
    }

    inline float getSpeakerRolloffFactor(const Speaker& speaker)
    {
        float factor = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_ROLLOFF_FACTOR,
            &factor);
        return factor;
    }

    inline float getSpeakerReferenceDistance(const Speaker& speaker)
    {
        float dist = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_REFERENCE_DISTANCE,
            &dist);
        return dist;
    }

    inline float getSpeakerMinGain(const Speaker& speaker)
    {
        float gain = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_MIN_GAIN,
            &gain);
        return gain;
    }

    inline float getSpeakerMaxGain(const Speaker& speaker)
    {
        float gain = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_MAX_GAIN,
            &gain);
        return gain;
    }

    inline float getSpeakerConeOuterGain(const Speaker& speaker)
    {
        float gain = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_CONE_OUTER_GAIN,
            &gain);
        return gain;
    }

    inline float getSpeakerConeInnerAngle(const Speaker& speaker)
    {
        float angle = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_CONE_INNER_ANGLE,
            &angle);
        return angle;
    }

    inline float getSpeakerConeOuterAngle(const Speaker& speaker)
    {
        float angle = -1.0f;
        CHECK_AL(alGetSourcef,
            speaker,
            AL_CONE_OUTER_ANGLE,
            &angle);
        return angle;
    }

    inline math::fvec3 getSpeakerPosition(const Speaker& speaker)
    {
        math::fvec3 pos = {};
        CHECK_AL(alGetSourcefv,
            speaker,
            AL_POSITION,
            &pos.x);
        return pos;
    }

    inline math::fvec3 getSpeakerVelocity(const Speaker& speaker)
    {
        math::fvec3 vel = {};
        CHECK_AL(alGetSourcefv,
            speaker,
            AL_VELOCITY,
            &vel.x);
        return vel;
    }

    inline math::fvec3 getSpeakerDirection(const Speaker& speaker)
    {
        math::fvec3 dir = {};
        CHECK_AL(alGetSourcefv,
            speaker,
            AL_DIRECTION,
            &dir.x);
        return dir;
    }

    inline bool getSpeakerRelative(const Speaker& speaker)
    {
        int rel = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_SOURCE_RELATIVE,
            &rel);
        return rel;
    }

    inline SpeakerType getSpeakerType(const Speaker& speaker)
    {
        int type = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_SOURCE_TYPE,
            &type);
        return static_cast<SpeakerType>(type);
    }

    inline bool getSpeakerLooping(const Speaker& speaker)
    {
        int looping = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_LOOPING,
            &looping);
        return looping;
    }

    inline Sound getSpeakerSound(const Speaker& speaker)
    {
        int sound = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_BUFFER,
            &sound);
        return sound;
    }

    inline SpeakerState getSpeakerState(const Speaker& speaker)
    {
        int state = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_SOURCE_STATE,
            &state);
        return static_cast<SpeakerState>(state);
    }

    inline size_t getSpeakerBuffersQueued(const Speaker& speaker)
    {
        int buffers = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_BUFFERS_QUEUED,
            &buffers);
        return static_cast<size_t>(buffers);
    }

    inline size_t getSpeakerBuffersProcessed(const Speaker& speaker)
    {
        int buffers = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_BUFFERS_PROCESSED,
            &buffers);
        return static_cast<size_t>(buffers);
    }

    inline int getSpeakerSecondOffset(const Speaker& speaker)
    {
        int offset = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_SEC_OFFSET,
            &offset);
        return offset;
    }

    inline int getSpeakerSampleOffset(const Speaker& speaker)
    {
        int offset = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_SAMPLE_OFFSET,
            &offset);
        return offset;
    }

    inline int getSpeakerByteOffset(const Speaker& speaker)
    {
        int offset = {};
        CHECK_AL(alGetSourcei,
            speaker,
            AL_BYTE_OFFSET,
            &offset);
        return offset;
    }

    inline void playSpeaker(const Speaker& speaker)
    {
        CHECK_AL(alSourcePlay, speaker);
    }

    inline void pauseSpeaker(const Speaker& speaker)
    {
        CHECK_AL(alSourcePause, speaker);
    }

    inline void stopSpeaker(const Speaker& speaker)
    {
        CHECK_AL(alSourceStop, speaker);
    }

    inline void rewindSpeaker(const Speaker& speaker)
    {
        CHECK_AL(alSourceRewind, speaker);
    }

    inline void queueSpeakerSound(const Speaker& speaker, Sound& sound)
    {
        // cant have a attached while streaming
        setSpeakerSound(speaker, nullptr);
        CHECK_AL(alSourceQueueBuffers, speaker, 1, &sound);
    }

    inline void queueSpeakerSounds(const Speaker& speaker, std::vector<Sound>& sounds)
    {
        // cant have a attached while streaming
        setSpeakerSound(speaker, nullptr);
        CHECK_AL(alSourceQueueBuffers, speaker, static_cast<ALsizei>(sounds.size()), &sounds.front());
    }

    inline void unqueueSpeakerSound(const Speaker& speaker, Sound& sound)
    {
        CHECK_AL(alSourceUnqueueBuffers, speaker, 1, &sound);
    }

    inline void unqueueSpeakerSounds(const Speaker& speaker, std::vector<Sound>& sounds)
    {
        CHECK_AL(alSourceUnqueueBuffers, speaker, static_cast<ALsizei>(sounds.size()), &sounds.front());
    }
}
