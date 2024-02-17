#pragma once

#include "quat.h"

namespace GLEEC::math
{
    template <typename T>
    quaternion<T> operator+ (const quaternion<T>& lhs, const quaternion<T>& rhs)
    {
        return { lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
    }

    template <typename T>
    quaternion<T> operator- (const quaternion<T>& lhs, const quaternion<T>& rhs)
    {
        return { lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
    }

    template <typename T>
    quaternion<T> operator- (const quaternion<T>& q)
    {
        return { -q.w, -q.x, -q.y, -q.z };
    }

    template <typename T>
    quaternion<T> operator* (const quaternion<T>& lhs, const quaternion<T>& rhs)
    {
        quaternion<T> t = {};

        t.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
        t.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
        t.y = lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z;
        t.z = lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x;

        return t;
    }

    template <typename T>
    quaternion<T> operator* (const quaternion<T>& lhs, const T scalar)
    {
        return { lhs.w * scalar, lhs.x * scalar, lhs.y * scalar, lhs.z * scalar };
    }

    template <typename T>
    quaternion<T> operator* (const T scalar, const quaternion<T>& rhs)
    {
        return rhs * scalar;
    }

    template <typename T>
    quaternion<T> operator* (const quaternion<T>& lhs, const vec<3, T>& rhs)
    {
        return lhs * quaternion<T>{ T(0), rhs.x, rhs.y, rhs.z };
    }

    template <typename T>
    quaternion<T> operator* (const vec<3, T>& lhs, const quaternion<T>& rhs)
    {
        return rhs * lhs;
    }

    template <typename T>
    quaternion<T> operator/ (const quaternion<T>& lhs, const T scalar)
    {
        return lhs * (T(1) / scalar);
    }

    template <typename T>
    quaternion<T> operator/ (const T scalar, const quaternion<T>& rhs)
    {
        return { scalar / rhs.w, scalar / rhs.x, scalar / rhs.y, scalar / rhs.z };
    }

    template <typename T>
    bool operator== (const quaternion<T>& lhs, const quaternion<T>& rhs)
    {
        return lhs.w == rhs.w && lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    template <typename T>
    bool operator!= (const quaternion<T>& lhs, const quaternion<T>& rhs)
    {
        return !(lhs == rhs);
    }
}
