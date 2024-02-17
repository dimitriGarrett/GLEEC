#pragma once

#include "math/vec.h"

namespace GLEEC::math
{
    template <typename T>
    struct plane3d
    {
        vec<3, T> normal = {};
        T d = static_cast<T>(0);

        plane3d() = default;

        template <typename X, typename Y, typename Z, typename W>
        plane3d(X a, Y b, Z c, W D)
            : normal(a, b, c), d(static_cast<T>(D))
        {
            normal = normalize(normal);
        }

        template <typename T2, typename W>
        plane3d(const vec<3, T2>& Normal, W D)
            : normal(Normal), d(static_cast<T>(D))
        {
        }
    };
}
