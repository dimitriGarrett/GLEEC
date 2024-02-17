#pragma once

#include "math/constants.h"
#include "algebra.h"

namespace GLEEC::math
{
    template <typename T>
    T max(const T a, const T b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    T min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    T clamp(const T val, const T lower, const T upper)
    {
        return max(lower, min(val, upper));
    }

    template <typename T>
    T sign(const T val)
    {
        return val < T(0) ? T(-1) : val == T(0) ? T(0) : T(1);
    }

    template <typename T>
    T signNon0(const T val)
    {
        return val < T(0) ? T(-1) : T(1);
    }

    template <typename T>
    T lerp(const T a, const T b, const T t)
    {
        return a + (b - a) * t;
    }

    template <typename T>
    T radians(const T deg)
    {
        return deg * (pi_t<T> / T(180));
    }

    template <typename T>
    T degrees(const T rad)
    {
        return rad * (T(180) / pi_t<T>);
    }

    template <typename T>
	T sin(T angle)
	{
		return static_cast<T>(std::sin(static_cast<double>(angle)));
	}

	template <typename T>
	T cos(T angle)
	{
		return static_cast<T>(std::cos(static_cast<double>(angle)));
	}

	template <typename T>
	T tan(T angle)
	{
		return static_cast<T>(std::tan(static_cast<double>(angle)));
	}

	template <typename T>
	T asin(T angle)
	{
		return static_cast<T>(std::asin(static_cast<double>(angle)));
	}

	template <typename T>
	T acos(T angle)
	{
		return static_cast<T>(std::acos(static_cast<double>(angle)));
	}

	template <typename T>
	T atan(T angle)
	{
		return static_cast<T>(std::atan(static_cast<double>(angle)));
	}

	template <typename T>
	T atan2(T y, T x)
	{
		return static_cast<T>(std::atan2(static_cast<double>(y), static_cast<double>(x)));
	}
}
