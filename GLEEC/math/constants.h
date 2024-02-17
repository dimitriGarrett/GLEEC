#pragma once

#include "math/utility/default_t"

namespace GLEEC::math
{
	template <typename T> inline constexpr T g_t = static_cast<T>(9.80665); // m/s^2
	template <typename T> inline constexpr T e_t = static_cast<T>(2.718281828459045);

	template <typename T> inline constexpr T pi_t = static_cast<T>(3.141592653589793);
	template <typename T> inline constexpr T invpi_t = static_cast<T>(1.0) / pi_t<T>;
	template <typename T> inline constexpr T twopi_t = static_cast<T>(2.0) * pi_t<T>;
	template <typename T> inline constexpr T piovertwo_t = pi_t<T> / static_cast<T>(2.0);

	inline constexpr default_t g = g_t<default_t>;
	inline constexpr default_t e = e_t<default_t>;

	inline constexpr default_t pi = pi_t<default_t>;
	inline constexpr default_t invpi = invpi_t<default_t>;
	inline constexpr default_t twopi = twopi_t<default_t>;
	inline constexpr default_t piovertwo = piovertwo_t<default_t>;
}
