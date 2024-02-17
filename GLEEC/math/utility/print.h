#pragma once

#include "to_string.h"

namespace GLEEC::math
{
	template <length_t l, typename T, typename stream_t>
	stream_t& operator<< (stream_t& stream, const vec<l, T>& v)
	{
		return stream << to_string(v);
	}

	template <typename T, typename stream_t>
	stream_t& operator<< (stream_t& stream, const quaternion<T>& v)
	{
		return stream << to_string(v);
	}

	template <length_t rows, length_t columns, typename T, typename stream_t>
	stream_t& operator<< (stream_t& stream, const matrix<rows, columns, T>& m)
	{
		return stream << to_string(m);
	}
}
