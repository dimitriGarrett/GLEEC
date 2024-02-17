#pragma once

#include "vec.h"

namespace GLEEC::math
{
    template <typename T>
    struct vec<3, T>
    {
        constexpr vec() = default;

        template <typename T2>
        constexpr vec(const T2 scalar)
            : x(static_cast<T>(scalar)),
              y(static_cast<T>(scalar)),
              z(static_cast<T>(scalar))
        {
        }

        template <typename T2, typename T3, typename T4>
        constexpr vec(const T2 X, const T3 Y, const T4 Z)
            : x(static_cast<T>(X)),
              y(static_cast<T>(Y)),
              z(static_cast<T>(Z))
        {
        }

        template <typename T2>
        constexpr vec(const vec<1, T2>& v)
            : x(static_cast<T>(v[0]))
        {
        }

        template <typename T2>
        constexpr vec(const vec<2, T2>& v)
            : x(static_cast<T>(v[0])),
              y(static_cast<T>(v[1]))
        {
        } 

        template <typename T2, typename Y2>
        constexpr vec(const vec<1, T2>& v, const Y2 Y)
            : vec(v.x, static_cast<T>(Y))
        {
        }

        template <typename T2, typename Z2>
        constexpr vec(const vec<2, T2>& v, const Z2 Z)
            : vec(v.x, v.y, static_cast<T>(Z))
        {
        }

        template <length_t L, typename T2>
        constexpr vec(const vec<L, T2>& v)
            : x(static_cast<T>(v[0])),
              y(static_cast<T>(v[1])),
              z(static_cast<T>(v[2]))
        {
        }

        static consteval length_t length()
        {
            return 3;
        }

        constexpr T& operator[] (const length_t i)
        {
            assert(i < length());

            switch (i)
            {
            case 0: return x;
            case 1: return y;
            case 2: return z;

            default:
#if GLEEC_DEBUG
            assert(false);
#endif
            return x;
            }
        }

        constexpr const T& operator[] (const length_t i) const
        {
            return const_cast<vec*>(this)->operator[](i);
        }

        T x = static_cast<T>(0);
        T y = static_cast<T>(0);
        T z = static_cast<T>(0);
    };
}
