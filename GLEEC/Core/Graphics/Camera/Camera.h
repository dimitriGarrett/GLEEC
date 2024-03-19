#pragma once

#include "math/utility/defines.h"

namespace GLEEC::Graphics
{
    struct Camera
    {
        math::fvec3 pos = {};
        math::fvec3 up = {};

        math::fmat4 projection = {};
        math::fmat4 view = {};
    };
}
