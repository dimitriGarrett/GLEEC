#pragma once

#include "operators.h"
#include "math/ops.h"

namespace GLEEC::math
{
    template <typename T>
    T dot(const vec<1, T>& v1, const vec<1, T>& v2)
    {
        return v1[0] * v2[0];
    }

    template <typename T>
    T dot(const vec<2, T>& v1, const vec<2, T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <typename T>
    T dot(const vec<3, T>& v1, const vec<3, T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <typename T>
    T dot(const vec<4, T>& v1, const vec<4, T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    template <length_t l, typename T>
    T dot(const vec<l, T>& v1, const vec<l, T>& v2)
    {
        vec<l, T> temp = v1 * v2;
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return (temp[N] + ...);
        );
    }

    template <length_t l, typename T>
    T length2(const vec<l, T>& v)
    {
        return dot(v, v);
    }

    template <length_t l, typename T>
    T length(const vec<l, T>& v)
    {
        return sqrt(length2(v));
    }

    template <length_t l, typename T>
    T mag2(const vec<l, T>& v)
    {
        return length2(v);
    }

    template <length_t l, typename T>
    T mag(const vec<l, T>& v)
    {
        return length(v);
    }

    template <length_t l, typename T>
    T cosAngle(const vec<l, T>& v1, const vec<l, T>& v2)
    {
        return dot(v1, v2) / (length(v1) * length(v2));
    }

    template <length_t l, typename T>
    T angle(const vec<l, T>& v1, const vec<l, T>& v2)
    {
        return acos(cosAngle(v1, v2));
    }

    template <typename T>
    vec<3, T> cross(const vec<3, T>& v1, const vec<3, T>& v2)
    {
        return 
        {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }

    template <length_t l, typename T>
    vec<l, T> normalize(const vec<l, T>& v)
    {
        return v / length(v);
    }

    template <length_t l, typename T>
    vec<l, T> min(const vec<l, T>& v1, const vec<l, T>& v2)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ (min(v1[N], v2[N]))... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> max(const vec<l, T>& v1, const vec<l, T>& v2)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ (max(v1[N], v2[N]))... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> clamp(const vec<l, T>& val, const vec<l, T>& lower, const vec<l, T>& upper)
    {
        return max(lower, min(val, upper));
    }

    template <length_t l, typename T>
    vec<l, T> sign(const vec<l, T>& v)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ sign(v[N])... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> signNon0(const vec<l, T>& v)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ signNon0(v[N])... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> lerp(const vec<l, T>& a, const vec<l, T>& b, const T t)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ lerp(a[N], b[N], t)... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> abs(const vec<l, T>& a)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ abs(a[N])... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> radians(const vec<l, T>& deg)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ radians(deg[N])... };
        );
    }

    template <length_t l, typename T>
    vec<l, T> degrees(const vec<l, T>& rad)
    {
        return GLEEC_MATH_INTERNAL_VEC_VARIADIC
        (
            return GLEEC_MATH_INTERNAL_VEC{ degrees(rad[N])... };
        );
    }
}
