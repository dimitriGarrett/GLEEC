#pragma once

#include "math/utility/defines.h"

namespace GLEEC::Graphics
{
    struct Vertex
    {
        // TODO: reorder as pos, uv.x, norm, uv.y?
        math::fvec3 pos  = {};
        math::fvec2 uv   = {};
        math::fvec3 norm = {};
    };
}
