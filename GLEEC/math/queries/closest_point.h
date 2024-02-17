#pragma once

#include "query.h"

namespace GLEEC::math::query
{
    template <typename T>
    vec<3, T> closestPoint(const aabb<T>& box, const point<T>& p)
    {
        return clamp(p, box.pos - box.half_extent, box.pos + box.half_extent);
    }

    template <typename T>
    vec<3, T> closestPoint(const point<T>& p, const aabb<T>& box)
    {
        return closestPoint(box, p);
    }

    template <typename T>
    vec<3, T> closestPoint(const obb<T>& box, const point<T>& p)
    {
        matrix<4, 4, T> mat = matrix<4, 4, T>(box.orientation);
        mat[3] = { p, T(1) };

        return mat * clamp(inverse(mat) * vec4(p, T(1)), vec4(-box.half_extent, T(1)), vec4(box.half_extent, T(1)));
    }

    template <typename T>
    vec<3, T> closestPoint(const point<T>& p, const obb<T>& box)
    {
        return closestPoint(box, p);
    }
}
