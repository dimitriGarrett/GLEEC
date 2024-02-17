#pragma once

#include "Error.h"

namespace GLEEC::Internal::Audio::OpenAL
{
    inline void setListenerGain(float gain)
    {
        CHECK_AL(alListenerf, AL_GAIN, gain);
    }

    inline void setListenerPosition(const math::fvec3& pos)
    {
        CHECK_AL(alListenerfv, AL_POSITION, &pos.x);
    }

    inline void setListenerVelocity(const math::fvec3& vel)
    {
        CHECK_AL(alListenerfv, AL_VELOCITY, &vel.x);
    }

    inline void setListenerOrientation(const math::fvec3& front, const math::fvec3& up)
    {
        math::vec<6, float> orientation = { front.x, front.y, front.z, up.x, up.y, up.z };
        CHECK_AL(alListenerfv, AL_ORIENTATION, &orientation[0]);
    }

#define GETF(type)\
    float temp = -1.0f;\
    CHECK_AL(alGetListenerf, type, &temp);\
    return temp;

#define GETFV(num, type)\
    math::vec<num, float> temp = {};\
    CHECK_AL(alGetListenerfv, type, &temp[0]);\
    return temp;

#define GETFV3(type) GETFV(3, type)
#define GETFV6(type) GETFV(6, type)

    inline float getListenerGain()
    {
        GETF(AL_GAIN);
    }

    inline math::fvec3 getListenerPosition()
    {
        GETFV3(AL_POSITION);
    }

    inline math::fvec3 getListenerVelocity()
    {
        GETFV3(AL_VELOCITY);
    }

    inline math::vec<6, float> getListenerOrientation()
    {
        GETFV6(AL_ORIENTATION);
    }

#undef GETF
#undef GETFV
#undef GETFV3
#undef GETFV6
}
