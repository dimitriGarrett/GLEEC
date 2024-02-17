#pragma once

#include "math/mat.h"
#include "math/quat.h"

#include <string>
#include <format>

namespace GLEEC::math
{
	template <length_t l, typename T>
	std::string to_string(const vec<l, T>& v)
	{
		std::string str = "vec";
		str += std::to_string(l);
		str += "[";

		for (length_t i = 0; i < l - 1; ++i)
		{
			str += std::to_string(v[i]);
			str += ", ";
		}

		str += std::to_string(v[l - 1]);
		str += "]";

		return str;
	}

	template <typename T>
	std::string to_string(const vec<2, T>& v)
	{
		return std::format("vec2[{}, {}]", v.x, v.y);
	}

	template <typename T>
	std::string to_string(const vec<3, T>& v)
	{
		return std::format("vec3[{}, {}, {}]", v.x, v.y, v.z);
	}

	template <typename T>
	std::string to_string(const vec<4, T>& v)
	{
		return std::format("vec4[{}, {}, {}, {}]", v.x, v.y, v.z, v.w);
	}

	template <typename T>
	std::string to_string(const quaternion<T>& q)
	{
		return std::format("quat[{}, {}, {}, {}]", q.w, q.x, q.y, q.z);
	}

	template <length_t rows, length_t columns, typename T>
	std::string to_string(const matrix<rows, columns, T>& q)
	{
		std::string temp = "mat";
		temp += std::to_string(rows);
		temp += "x";
		temp += std::to_string(columns);
		temp += '\n';

		for (length_t i = 0; i < rows; ++i)
		{
			std::string v = to_string(q.row(i));
			temp += v.substr(v.find('['));
			if (i != rows - 1) temp += '\n';
		}

		return temp;
	}
}

template <GLEEC::math::length_t l, typename T>
struct std::formatter<GLEEC::math::vec<l, T>> : std::formatter<std::string>
{
    auto format(const GLEEC::math::vec<l, T>& vec, format_context& ctx) const
    {
        return formatter<string>::format(GLEEC::math::to_string(vec), ctx);
    }
};

template <GLEEC::math::length_t rows, GLEEC::math::length_t columns, typename T>
struct std::formatter<GLEEC::math::matrix<rows, columns, T>> : std::formatter<std::string>
{
    auto format(const GLEEC::math::matrix<rows, columns, T>& mat, format_context& ctx) const
    {
        return formatter<string>::format(GLEEC::math::to_string(mat), ctx);
    }
};

template <typename T>
struct std::formatter<GLEEC::math::quaternion<T>> : std::formatter<std::string>
{
    auto format(const GLEEC::math::quaternion<T>& q, format_context& ctx) const
    {
        return formatter<string>::format(GLEEC::math::to_string(q), ctx);
    }
};
