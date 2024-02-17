#pragma once

#include <cmath>

namespace GLEEC::math
{
	template <typename T>
	T sqrt(T num)
	{
		return static_cast<T>(std::sqrt(static_cast<double>(num)));
	}

	template <typename T>
	T invsqrt(T num)
	{
		return static_cast<T>(1.0) / sqrt(num);
	}

	template <typename T>
	T abs(T num)
	{
		return num < 0 ? -num : num;
	}

	template <typename T, typename... Args>
	T avg(Args&&... args)
	{
		return (args + ...) * (static_cast<T>(1.0) / sizeof...(Args));
	}

	template <typename T>
	T avg()
	{
		return 0;
	}
}
