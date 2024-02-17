#pragma once

#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "math/utility/cseq.h"

namespace GLEEC::math
{
	template <length_t l, typename T>
	constexpr vec<l, T>& operator+= (vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] += rhs[N]), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator+= (vec<l, T>& lhs, const T scalar)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] += scalar), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator-= (vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] -= rhs[N]), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator-= (vec<l, T>& lhs, const T scalar)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] -= scalar), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator*= (vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] *= rhs[N]), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator*= (vec<l, T>& lhs, const T scalar)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] *= scalar), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator/= (vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] /= rhs[N]), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T>& operator/= (vec<l, T>& lhs, const T scalar)
	{
        const T inv = T(1) / scalar;
		GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			((lhs[N] *= inv), ...);
		);

		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator+ (const vec<l, T>& lhs)
	{
		return lhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator- (const vec<l, T>& lhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (-lhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator+ (const vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (lhs[N] + rhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator+ (const vec<l, T>& lhs, T scalar)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (lhs[N] + scalar)... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator+ (T scalar, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (scalar + rhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator- (const vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		return lhs + (-rhs);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator- (const vec<l, T>& lhs, const T scalar)
	{
		return lhs + (-scalar);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator- (const T scalar, const vec<l, T>& rhs)
	{
		return -scalar + rhs;
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator* (const vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (lhs[N] * rhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator* (const vec<l, T>& lhs, const T scalar)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (lhs[N] * scalar)... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator* (T scalar, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (scalar * rhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator/ (const vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (lhs[N] / rhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator/ (const vec<l, T>& lhs, const T scalar)
	{
		return lhs * (static_cast<T>(1.0) / scalar);
	}

	template <length_t l, typename T>
	constexpr vec<l, T> operator/ (const T scalar, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return GLEEC_MATH_INTERNAL_VEC{ (scalar / rhs[N])... };
		);
	}

	template <length_t l, typename T>
	constexpr bool operator== (const vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		return GLEEC_MATH_INTERNAL_VEC_VARIADIC
		(
			return ((lhs[N] == rhs[N]) && ...);
		);
	}

	template <length_t l, typename T>
	constexpr bool operator!= (const vec<l, T>& lhs, const vec<l, T>& rhs)
	{
		return !(lhs == rhs);
	}
}
