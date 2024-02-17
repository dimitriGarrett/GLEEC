#pragma once

#include "DistanceModel.h"

#include <string_view>

namespace GLEEC::Internal::Audio::OpenAL
{
    inline std::string_view getVendor()
    {
        const ALchar* str = CHECK_AL(alGetString, AL_VENDOR);
        return str == nullptr ? "Unknown Vendor (Error Occured)" : str;
    }

    inline std::string_view getVersion()
    {
        const ALchar* str = CHECK_AL(alGetString, AL_VERSION);
        return str == nullptr ? "Unknown Version (Error Occured)" : str;
    }

    inline std::string_view getRenderer()
    {
        const ALchar* str = CHECK_AL(alGetString, AL_RENDERER);
        return str == nullptr ? "Unknown Renderer (Error Occured)" : str;
    }

    inline std::string_view getExtensions()
    {
        const ALchar* str = CHECK_AL(alGetString, AL_EXTENSIONS);
        return str == nullptr ? "Unknown Extensions (Error Occured)" : str;
    }

    inline void setGlobalDopplerFactor(float doppler)
    {
        CHECK_AL(alDopplerFactor, doppler);
    }

    inline void setGlobalDistanceModel(DistanceModel model)
    {
        CHECK_AL(alDistanceModel, static_cast<int>(model));
    }

    inline void setGlobalSpeedOfSound(float speed)
    {
        CHECK_AL(alSpeedOfSound, speed);
    }

    inline float getGlobalDopplerFactor()
    {
        return CHECK_AL(alGetFloat, AL_DOPPLER_FACTOR);
    }

    inline DistanceModel getGlobalDistanceModel()
    {
        return static_cast<DistanceModel>(CHECK_AL(alGetFloat, AL_DISTANCE_MODEL));
    }

    inline float getGlobalSpeedOfSound()
    {
        return CHECK_AL(alGetFloat, AL_SPEED_OF_SOUND);
    }
}
