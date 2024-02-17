#pragma once

#include "math/vec.h"

#include <cmath>

namespace GLEEC::math
{
    template <typename T>
    struct quaternion
    {
        constexpr quaternion() = default;

        constexpr quaternion(const vec<3, T>& eulerAngles)
        {
            // source: https://danceswithcode.net/engineeringnotes/quaternions/quaternions.html

            const T cu = cos(eulerAngles.x * T(0.5));
            const T cv = cos(eulerAngles.y * T(0.5));
            const T cw = cos(eulerAngles.z * T(0.5));

            const T su = sin(eulerAngles.x * T(0.5));
            const T sv = sin(eulerAngles.y * T(0.5));
            const T sw = sin(eulerAngles.z * T(0.5));

            w = cu * cv * cw + su * sv * sw;
            x = su * cw * cw - cu * sv * sw;
            y = cu * sv * cw + su * cv * sw;
            z = cu * cv * sw - su * sv * cw;
        }

        constexpr quaternion(const T angle, const vec<3, T>& axis)
        {
            constexpr T half = static_cast<T>(0.5) * angle;
            const T c = cos(half);
            const T s = sin(half);

            w = c;

            vec<3, T> i = axis * s;
            x = i.x;
            y = i.y;
            z = i.z;
        }

        constexpr quaternion(T yaw, T pitch, T roll)
            : quaternion(vec<3, T>{ yaw, pitch, roll })
        {
        }

        constexpr quaternion(T W, T X, T Y, T Z)
            : w(W), x(X), y(Y), z(Z)
        {
        }

        T w = static_cast<T>(1.0);
        T x = static_cast<T>(0.0);
        T y = static_cast<T>(0.0);
        T z = static_cast<T>(0.0);
    };
}
