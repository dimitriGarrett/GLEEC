#pragma once

#include "math/utility/length_t.h"
#include "math/utility/cseq.h"

#include <cassert>

namespace GLEEC::math
{
#define GLEEC_MATH_INTERNAL_VEC vec<l, T>
#define GLEEC_MATH_INTERNAL_VEC_VARIADIC(f) [&]<length_t... N>(cseq<N...>) { f }(make_cseq<l>{})

    template <length_t l, typename T>
    struct vec
    {
        constexpr vec() = default;

        constexpr vec(const T scalar)
        {
            GLEEC_MATH_INTERNAL_VEC_VARIADIC
            (
                ((data[N] = scalar), ...);
            );
        }

        constexpr vec(T arr[l])
            : vec(arr, make_cseq<l>{})
        {
        }

        constexpr vec(std::initializer_list<T> scalars)
        {
            GLEEC_MATH_INTERNAL_VEC_VARIADIC
            (
                ((data[N] = *(scalars.begin() + N)), ...);
            );
        }

        template <length_t L, typename T2>
        constexpr vec(const vec<L, T2>& v)
        {
            GLEEC_MATH_INTERNAL_VEC_VARIADIC
            (
                ((data[N] = static_cast<T>(v[N])), ...);
            );
        }

        static consteval length_t length()
        {
            return l;
        }

        constexpr T& operator[] (const length_t i)
        {
            assert(i < length());

            return data[i];
        }

        constexpr const T& operator[] (const length_t i) const
        {
            return const_cast<vec*>(this)->operator[](i);
        }

    private:
        template <length_t... N>
        constexpr vec(T arr[l], cseq<N...>)
            : data{ arr[N]... }
        {
        }

        T data[l] = { static_cast<T>(0) };
    };
}
