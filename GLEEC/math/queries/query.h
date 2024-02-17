#pragma once

#include "math/mat.h"
#include "math/plane.h"

#include "math/ops.h"

namespace GLEEC::Physics
{
    struct AABBCollider;
    struct OBBCollider;
}

namespace GLEEC::math
{
    template <typename T> using point = vec<3, T>;

    template <typename T>
    struct ray
    {
        point<T> a = {};
        vec<3, T> dir = {};
    };

    template <typename T>
    struct line_segment
    {
        point<T> a = {};
        point<T> b = {};
    };

    template <typename T>
    struct aabb
    {
        point<T> pos = {};
        vec<3, T> half_extent = {};
    };

    template <typename T>
    struct obb
    {
        matrix<3, 3, T> orientation = {};

        point<T> pos = {};
        vec<3, T> half_extent = {};
    };
}
