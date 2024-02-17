#pragma once

#include "Error.h"

namespace GLEEC::Internal::Audio::OpenAL
{
    using Sound = ALuint;

    inline Sound createSound()
    {
        Sound temp = {};
        CHECK_AL(alGenBuffers, 1, &temp);
        return temp;
    }

    inline void destroySound(Sound& sound)
    {
        CHECK_AL(alDeleteBuffers, 1, &sound);
    }

    inline ALenum soundFormat(int channels)
    {
        return channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    }

    inline void fillSound(Sound& sound, const short* data, int channels, ALsizei size, ALsizei frequency)
    {
        CHECK_AL(alBufferData, sound, soundFormat(channels), data, size, frequency);
    }

    inline ALint getSoundFrequency(const Sound& sound)
    {
        ALint freq;
        CHECK_AL(alGetBufferi, sound, AL_FREQUENCY, &freq);
        return freq;
    }

    inline ALint getSoundBits(const Sound& sound)
    {
        ALint bits;
        CHECK_AL(alGetBufferi, sound, AL_BITS, &bits);
        return bits;
    }

    inline ALint getSoundChannels(const Sound& sound)
    {
        ALint channels;
        CHECK_AL(alGetBufferi, sound, AL_CHANNELS, &channels);
        return channels;
    }

    inline ALint getSoundSize(const Sound& sound)
    {
        ALint size;
        CHECK_AL(alGetBufferi, sound, AL_BITS, &size);
        return size;
    }
}
