#pragma once

#include "Device.h"

namespace GLEEC::Internal::Audio::OpenAL
{
    using Context = ALCcontext*;

    inline Device getContextsDevice(Context context)
    {
        return context == nullptr ? Device{} : Device{ CHECK_ALC(alcGetContextsDevice, alcGetContextsDevice(context), context) };
    }

    inline Context createAudioContext(Device device)
    {
        // nowhere online have i found how to structure the
        // attrlist parameter so boohoo if anyone cares
        // doubt it
        return CHECK_ALC(alcCreateContext, device, device, nullptr);
    }

    inline void makeAudioContextCurrent(Context context)
    {
        CHECK_ALC(alcMakeContextCurrent, getContextsDevice(context), context);
    }

    inline void makeAudioContextCurrent(decltype(nullptr))
    {
        CHECK_ALC(alcMakeContextCurrent, Device{}, nullptr);
    }

    inline void processAudioContext(Context context)
    {
        CHECK_ALC(alcProcessContext, getContextsDevice(context), context);
    }

    inline void suspendAudioContext(Context context)
    {
        CHECK_ALC(alcSuspendContext, getContextsDevice(context), context);
    }

    inline void destroyAudioContext(Context context, Device device)
    {
        CHECK_ALC(alcDestroyContext, device, context);
    }

    inline void destroyAudioContext(Context context)
    {
        destroyAudioContext(context, getContextsDevice(context));
    }

    inline Context getCurrentContext()
    {
        return CHECK_ALC(alcGetCurrentContext, getContextsDevice(alcGetCurrentContext()));
    }
}
