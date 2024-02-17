#pragma once

#include "vec.h"

namespace GLEEC::math
{
    template <typename T>
    struct vec<2, T>
    {
        constexpr vec() = default;

        template <typename T2>
        constexpr vec(const T2 scalar)
            : x(static_cast<T>(scalar)),
              y(static_cast<T>(scalar))
        {
        }

        template <typename T2, typename T3>
        constexpr vec(const T2 X, const T3 Y)
            : x(static_cast<T>(X)),
              y(static_cast<T>(Y))
        {
        }

        template <typename T2>
        constexpr vec(const vec<1, T2>& v)
            : x(static_cast<T>(v[0]))
        {
        }

        template <typename T2, typename Y2>
        constexpr vec(const vec<1, T2>& v, const Y2 Y)
            : vec(v.x, static_cast<T>(Y))
        {
        }

        template <length_t l, typename T2>
        constexpr vec(const vec<l, T2>& v)
            : x(static_cast<T>(v[0])),
              y(static_cast<T>(v[1]))
        {
        }

        static consteval length_t length()
        {
            return 2;
        }

        constexpr T& operator[] (const length_t i)
        {
            assert(i < length());

            switch(i)
            {
            case 0: return x;
            case 1: return y;

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
    };
}
