#pragma once

#include "Error.h"

#include <cstdint>

namespace GLEEC::Internal::Audio::OpenAL
{
    enum class DistanceModel : int32_t
    {
        INVERSE_DISTANCE = AL_INVERSE_DISTANCE,
        INVERSE_DISTANCE_CLAMPED = AL_INVERSE_DISTANCE_CLAMPED,
        LINEAR_DISTANCE = AL_LINEAR_DISTANCE,
        LINEAR_DISTANCE_CLAMPED = AL_LINEAR_DISTANCE_CLAMPED,
        EXPONENT_DISTANCE = AL_EXPONENT_DISTANCE,
        EXPONENT_DISTANCE_CLAMPED = AL_EXPONENT_DISTANCE_CLAMPED,

        NONE = AL_NONE,
    };
}
