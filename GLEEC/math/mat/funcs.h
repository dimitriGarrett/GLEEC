#pragma once

#include "operators.h"
#include "math/quat.h"

namespace GLEEC::math
{
	template <typename T>
	matrix<3, 3, T> toMat3Normalized(const quaternion<T>& q)
	{
		return matrix<3, 3, T>
		{
            static_cast<T>(1) - static_cast<T>(2) * (q.y * q.y + q.z * q.z), static_cast<T>(2) * (q.x * q.y - q.w * q.z), static_cast<T>(2) * (q.x * q.z + q.w * q.y),
			static_cast<T>(2) * (q.x * q.y + q.w * q.z), static_cast<T>(1) - static_cast<T>(2) * (q.x * q.x + q.z * q.z), static_cast<T>(2) * (q.y * q.z - q.w * q.x),
			static_cast<T>(2) * (q.x * q.z - q.w * q.y), static_cast<T>(2) * (q.y * q.z + q.w * q.x), static_cast<T>(1) - static_cast<T>(2) * (q.x * q.x + q.y * q.y),
		};
	}

	template <typename T>
	matrix<3, 3, T> toMat3(const quaternion<T>& q)
	{
        return toMat3Normalized(normalize(q));
	}

	template <typename T>
	matrix<4, 4, T> toMat4(const quaternion<T>& q)
	{
		return toMat3(q);
	}

    template <typename T>
    quaternion<T> toQuatNormalized(const matrix<3, 3, T>& m)
	{
		T t = m(0, 0) + m(1, 1) + m(2, 2);
		T s = static_cast<T>(0.0);

		if (t > static_cast<T>(0))
		{
			s = static_cast<T>(1.0) / (sqrt(t + static_cast<T>(1.0)) * static_cast<T>(2));

			return { static_cast<T>(0.25) / s, (m(2, 1) - m(1, 2)) * s, (m(0, 2) - m(2, 0)) * s, (m(1, 0) - m(0, 1)) * s };
		}

		else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2))
		{
			s = static_cast<T>(1.0) / (sqrt(static_cast<T>(1.0) + m(0, 0) - m(1, 1) - m(2, 2)) * static_cast<T>(2));

			return { (m(2, 1) - m(1, 2)) * s, static_cast<T>(0.25) / s, (m(0, 1) + m(1, 0)) * s, (m(0, 2) + m(2, 0)) * s };
		}

		else if (m(1, 1) > m(2, 2))
		{
			s = static_cast<T>(1.0) / (sqrt(static_cast<T>(1.0) + m(1, 1) - m(0, 0) - m(2, 2)) * static_cast<T>(2));

			return { (m(0, 2) - m(2, 0)) * s, (m(0, 1) + m(1, 0)) * s, static_cast<T>(0.25) / s, (m(1, 2) + m(2, 1)) * s };
		}

		else
		{
			s = static_cast<T>(1.0) / (sqrt(static_cast<T>(1.0) + m(2, 2) - m(0, 0) - m(1, 1)) * static_cast<T>(2));

			return { (m(1, 0) - m(0, 1)) * s, (m(0, 2) + m(2, 0)) * s, (m(1, 2) + m(2, 1)) * s, static_cast<T>(0.25) / s };
		}
	}

	template <typename T>
	quaternion<T> toQuat(const matrix<3, 3, T>& m)
    {
        return normalize(toQuatNormalized(m));
    }

	template <typename T>
	quaternion<T> toQuat(const matrix<4, 4, T>& m)
	{
		return toQuat(matrix<3, 3, T>(m));
	}

	template <length_t d, typename T>
	matrix<d, d, T> luDecomposition(matrix<d, d, T> m)
	{
		// This is an in-place version, from https://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/doolittle.pdf
		// (Translated from Fortran)
		for (length_t i = 0; i < d; ++i)
		{
			for (length_t j = i; j < d; ++j)
			{
				for (length_t k = 0; k < i; ++k)
					m(i, j) -= m(i, k) * m(k, j);
			}

			T mult = m(i, i) == static_cast<T>(0) ? static_cast<T>(1.0) : static_cast<T>(1.0) / m(i, i);
			for (length_t j = i + 1; j < d; ++j)
			{
				for (length_t k = 0; k < i; ++k)
					m(j, i) -= m(j, k) * m(k, i);
				m(j, i) *= mult;
			}
		}
		return m;
	}

	// Retrieve the lower triangular matrix from m using lu decomposition
	template <length_t d, typename T>
	matrix<d, d, T> lower(const matrix<d, d, T>& m)
	{
		matrix<d, d, T> temp = matrix<d, d, T>(static_cast<T>(1));
		matrix<d, d, T> dec = luDecomposition(m);

		for (length_t i = 0; i < d; ++i)
		{
			for (length_t j = i + 1; j < d; ++j)
				temp(j, i) = dec(j, i);
		}

		return temp;
	}

	// Retrieve the upper triangular matrix from m using lu decomposition
	template <length_t d, typename T>
	matrix<d, d, T> upper(const matrix<d, d, T>& m)
	{
		matrix<d, d, T> temp = luDecomposition(m);

		for (length_t i = 0; i < d; ++i)
		{
			for (length_t j = i + 1; j < d; ++j)
				temp(j, i) = 0;
		}

		return temp;
	}

	template <length_t d, typename T>
	T determinant(const matrix<d, d, T>& m)
	{
		matrix<d, d, T> lu = luDecomposition(m);
		T det = lu(0, 0);
		for (length_t i = 1; i < d; ++i) det *= lu(i, i);
		return det;
	}

	template <typename T>
	T determinant(const matrix<2, 2, T>& m)
	{
		return m(0, 0) * m(1, 1)
			 - m(0, 1) * m(1, 0);
	}

	template <typename T>
	T determinant(const matrix<3, 3, T>& m)
	{
		using sm = matrix<2, 2, T>;

		return m(0, 0) * determinant(sm{ m(1, 1), m(1, 2), m(2, 1), m(2, 2) })
			 - m(0, 1) * determinant(sm{ m(1, 0), m(1, 2), m(2, 0), m(2, 2) })
			 + m(0, 2) * determinant(sm{ m(1, 0), m(1, 1), m(2, 0), m(2, 1) });
	}

	template <typename T>
	T determinant(const matrix<4, 4, T>& m)
	{
		using sm = matrix<3, 3, T>;

		return m(0, 0) * determinant(sm{ m(1, 1), m(1, 2), m(1, 3), m(2, 1), m(2, 2), m(2, 3), m(3, 1), m(3, 2), m(3, 3) })
			 - m(0, 1) * determinant(sm{ m(1, 0), m(1, 2), m(1, 3), m(2, 0), m(2, 2), m(2, 3), m(3, 0), m(3, 2), m(3, 3) })
			 + m(0, 2) * determinant(sm{ m(1, 0), m(1, 1), m(1, 3), m(2, 0), m(2, 1), m(2, 3), m(3, 0), m(3, 1), m(3, 3) })
			 - m(0, 3) * determinant(sm{ m(1, 0), m(1, 1), m(1, 2), m(2, 0), m(2, 1), m(2, 2), m(3, 0), m(3, 1), m(3, 2) });
	}

	template <length_t d, typename T>
	bool singular(const matrix<d, d, T>& m)
	{
		return determinant(m) != 0;
	}

	template <typename T>
	matrix<2, 2, T> inverse(const matrix<2, 2, T>& m)
	{
		T det = determinant(m);
		return det == static_cast<T>(0) ? matrix<2, 2, T>(static_cast<T>(1)) : matrix<2, 2, T>
		{
			m(1, 1), -m(0, 1),
		   -m(1, 0),  m(0, 0)
		} *static_cast<T>(1) / det;
	}

	template <typename T>
	matrix<3, 3, T> inverse(const matrix<3, 3, T>& m)
	{
		using sm = matrix<2, 2, T>;

		T det = determinant(m);
		return det == static_cast<T>(0) ? matrix<3, 3, T>(static_cast<T>(1)) : matrix<3, 3, T>
		{
			m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1), m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2), m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1),
			m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2), m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0), m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2),
			m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0), m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1), m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)
		} *static_cast<T>(1) / det;
	}

    template <length_t r, length_t c, typename T>
    void swapRows(matrix<r, c, T>& m, uint32_t r1, uint32_t r2)
    {
        GLEEC_MATH_INTERNAL_MAT_VARIADIC
        (
            c,
            (std::swap(m(r1, N), m(r2, N)), ...);
        );
    }

    template <length_t d, typename T>
	matrix<d, d, T> cofactor(const matrix<d, d, T>& m)
	{
		matrix<d, d, T> temp = {};
		matrix<d - 1, d - 1, T> c = {};

		for (int j = 0; j < d; ++j)
		{
			for (int i = 0; i < d; ++i)
			{
				int i1 = 0;

				for (int ii = 0; ii < d; ++ii)
				{
					if (ii == i)
						continue;
					int j1 = 0;
					
					for (int jj = 0; jj < d; ++jj)
					{
						if (jj == j)
							continue;
						c[i1][j1] = m[ii][jj];
						++j1;
					}
					++i1;
				}

				T det = determinant(c);
				temp[i][j] = ::pow(-1.0, static_cast<double>(i + j) + 2.0) * det;
			}
		}

		return temp;
	}

    template <length_t d, typename T>
    matrix<d, d, T> adjoint(const matrix<d, d, T>& m)
    {
        return transpose(cofactor(m));
    }

	template <length_t d, typename T>
	matrix<d, d, T> inverse(const matrix<d, d, T>& m)
	{
        return (static_cast<T>(1) / determinant(m)) * adjoint(m);
	}

	template <typename T>
	matrix<4, 4, T> projectionVulkan(T fov, T aspect, T near, T far)
	{
		//https://vincent-p.github.io/posts/vulkan_perspective_matrix/

		T g = static_cast<T>(1.0f) / tan(fov * static_cast<T>(0.5));
		T k = near / (far - near);

		constexpr T z = static_cast<T>(0.0f);

		return matrix<4, 4, T>
		{
			g / aspect, z, z, z,
			z, -g, z, z,
			z, z, k, far* k,
			z, z, static_cast<T>(-1.0f), z
		};
	}

    template <typename T>
    matrix<3, 3, T> normalize(const matrix<3, 3, T>& m)
    {
        matrix<3, 3, T> temp = {};
		temp[0] = normalize(m[0]);
		temp[1] = normalize(m[1]);
		temp[2] = normalize(m[2]);
		return temp;
    }

	template <typename T>
	matrix<4, 4, T> lookAtRH(const vec<3, T>& eye, const vec<3, T>& center, const vec<3, T>& up)
	{
		const vec<3, T> f(normalize(center - eye));
		const vec<3, T> s(normalize(cross(f, up)));
		const vec<3, T> u(cross(s, f));

		matrix<4, 4, T> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -dot(s, eye);
		Result[3][1] = -dot(u, eye);
		Result[3][2] =  dot(f, eye);
		return Result;
	}

	template <typename T>
	vec<3, T> modelPosition(const matrix<4, 4, T>& m)
	{
		return m[3];
	}

	template <typename T>
	vec<3, T> modelScale(const matrix<4, 4, T>& m)
	{
		return { length(m[0]), length(m[1]), length(m[2]) };
	}

	template <typename T>
	quaternion<T> modelOrientation(const matrix<3, 3, T>& m)
	{
		return toQuat(normalize(m));
	}

	template <typename T>
	quaternion<T> modelOrientation(const matrix<4, 4, T>& m)
	{
		return modelOrientation(matrix<3, 3, T>(m));
	}

	template <typename T>
	matrix<4, 4, T> translate(const matrix<4, 4, T>& m, const vec<3, T>& v)
	{
		// taken from glm source code
		matrix<4, 4, T> result = m;
		result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return result;
	}

	template <typename T>
	matrix<4, 4, T> scale(const matrix<4, 4, T>& m, const vec<3, T>& v)
	{
		matrix<4, 4, T> temp = m;
		temp[0] *= v[0];
		temp[1] *= v[1];
		temp[2] *= v[2];
		return temp;
	}

    template <typename T>
    matrix<4, 4, T> scale(const matrix<4, 4, T>& m, const T& scalar)
    {
        return scale(m, { scalar, scalar, scalar });
    }

    template <typename T>
    matrix<4, 4, T> rotate(const matrix<4, 4, T>& m, T angle, const vec<3, T>& Axis)
    {
        // source: glm::rotate
		T const a = angle;
		T const c = cos(a);
		T const s = sin(a);

		vec<3, T> axis(normalize(Axis));
		vec<3, T> temp((T(1) - c) * axis);

		matrix<4, 4, T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		matrix<4, 4, T> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
    }

    template <typename T>
    matrix<4, 4, T> rotate(const matrix<4, 4, T>& m, const quaternion<T>& q)
    {
        return m * toMat4(q);
    }

    template <typename T>
    vec<4, T> rotate(const vec<4, T>& v, const matrix<4, 4, T>& m)
    {
        return m * v;
    }

    template <typename T>
    vec<3, T> rotate(const vec<3, T>& v, const matrix<4, 4, T>& m)
    {
        return rotate(vec<4, T>(v, T(1)), m);
    }

	template <typename T>
	matrix<4, 4, T> interpolateModel(const matrix<4, 4, T>& oldModel, const matrix<4, 4, T>& newModel, T alpha)
	{
		const vec<3, T> oldPos = modelPosition(oldModel);
		const vec<3, T> newPos = modelPosition(newModel);

		const vec<3, T> pos = lerp(oldPos, newPos, alpha);

		const vec<3, T> oldScale = modelScale(oldModel);
		const vec<3, T> newScale = modelScale(newModel);

		const vec<3, T> size = lerp(oldScale, newScale, alpha);

		const quaternion<T> oldOrientation = modelOrientation(oldModel);
		const quaternion<T> newOrientation = modelOrientation(newModel);

		const quaternion<T> orientation = lerpFast(oldOrientation, newOrientation, alpha);

        matrix<4, 4, T> temp = scale(rotate(matrix<4, 4, T>(1), orientation), size);
        temp[3] = { pos, T(1) };
        return temp;
	}

	template <length_t r, length_t c, typename T>
	matrix<c, r, T> transpose(const matrix<r, c, T>& m)
	{
		if constexpr (c == r)
		{
			// source: http://paulbourke.net/miscellaneous/determinant/
			matrix<c, r, T> temp = m;
			for (length_t i = 1; i < r; ++i)
			{
				for (length_t j = 0; j < i; ++j)
				{
					T t = temp(j, i);
					temp(j, i) = temp(i, j);
					temp(i, j) = t;
				}
			}
			return temp;
		}

		else
		{
			matrix<c, r, T> temp;
			for (length_t i = 0; i < r; ++i)
				for (length_t j = 0; j < c; ++j)
					temp(j, i) = m(i, j);
			return temp;
		}
	}

	template <typename T>
	matrix<2, 2, T> transpose(const matrix<2, 2, T>& m)
	{
		matrix<2, 2, T> temp = m;

		temp(1, 0) = m(0, 1);
		temp(0, 1) = m(1, 0);

		return temp;
	}

	template <typename T>
	matrix<3, 2, T> transpose(const matrix<2, 3, T>& m)
	{
		matrix<3, 2, T> temp;

		temp(0, 0) = m(0, 0);
		temp(1, 0) = m(0, 1);
		temp(2, 0) = m(0, 2);

		temp(0, 1) = m(1, 0);
		temp(1, 1) = m(1, 1);
		temp(2, 1) = m(1, 2);

		return temp;
	}

	template <typename T>
	matrix<4, 2, T> transpose(const matrix<2, 4, T>& m)
	{
		matrix<4, 2, T> temp;

		temp(0, 0) = m(0, 0);
		temp(1, 0) = m(0, 1);
		temp(2, 0) = m(0, 2);
		temp(3, 0) = m(0, 3);

		temp(0, 1) = m(1, 0);
		temp(1, 1) = m(1, 1);
		temp(2, 1) = m(1, 2);
		temp(3, 1) = m(1, 3);

		return temp;
	}

	template <typename T>
	matrix<2, 3, T> transpose(const matrix<3, 2, T>& m)
	{
		matrix<2, 3, T> temp;

		temp(0, 0) = m(0, 0);
		temp(1, 0) = m(0, 1);

		temp(0, 1) = m(1, 0);
		temp(1, 1) = m(1, 1);

		temp(0, 2) = m(2, 0);
		temp(1, 2) = m(2, 1);

		return temp;
	}

	template <typename T>
	matrix<3, 3, T> transpose(const matrix<3, 3, T>& m)
	{
		matrix<3, 3, T> temp = m;

		temp(1, 0) = m(0, 1);
		temp(0, 1) = m(1, 0);

		temp(0, 2) = m(2, 0);
		temp(2, 0) = m(0, 2);

		temp(2, 1) = m(1, 2);
		temp(1, 2) = m(2, 1);

		return temp;
	}

	template <typename T>
	matrix<4, 3, T> transpose(const matrix<3, 4, T>& m)
	{
		matrix<4, 3, T> temp;

		temp(0, 0) = m(0, 0);
		temp(1, 0) = m(0, 1);
		temp(2, 0) = m(0, 2);
		temp(3, 0) = m(0, 3);

		temp(0, 1) = m(1, 0);
		temp(1, 1) = m(1, 1);
		temp(2, 1) = m(1, 2);
		temp(3, 1) = m(1, 3);

		temp(0, 2) = m(2, 0);
		temp(1, 2) = m(2, 1);
		temp(2, 2) = m(2, 2);
		temp(3, 2) = m(2, 3);

		return temp;
	}

	template <typename T>
	matrix<2, 4, T> transpose(const matrix<4, 2, T>& m)
	{
		matrix<2, 4, T> temp;

		temp(0, 0) = m(0, 0);
		temp(1, 0) = m(0, 1);

		temp(0, 1) = m(1, 0);
		temp(1, 1) = m(1, 1);

		temp(0, 2) = m(2, 0);
		temp(1, 2) = m(2, 1);

		temp(0, 3) = m(3, 0);
		temp(1, 3) = m(3, 1);

		return temp;
	}

	template <typename T>
	matrix<3, 4, T> transpose(const matrix<4, 3, T>& m)
	{
		matrix<3, 4, T> temp;

		temp(0, 0) = m(0, 0);
		temp(1, 0) = m(0, 1);
		temp(2, 0) = m(0, 2);

		temp(0, 1) = m(1, 0);
		temp(1, 1) = m(1, 1);
		temp(2, 1) = m(1, 2);

		temp(0, 2) = m(2, 0);
		temp(1, 2) = m(2, 1);
		temp(2, 2) = m(2, 2);

		temp(0, 3) = m(3, 0);
		temp(1, 3) = m(3, 1);
		temp(2, 3) = m(3, 2);

		return temp;
	}

	template <typename T>
	matrix<4, 4, T> transpose(const matrix<4, 4, T>& m)
	{
		matrix<4, 4, T> temp = m;

		temp(1, 0) = m(0, 1);
		temp(0, 1) = m(1, 0);

		temp(0, 2) = m(2, 0);
		temp(2, 0) = m(0, 2);

		temp(2, 1) = m(1, 2);
		temp(1, 2) = m(2, 1);

		temp(3, 0) = m(0, 3);
		temp(0, 3) = m(3, 0);

		temp(3, 1) = m(1, 3);
		temp(1, 3) = m(3, 1);

		temp(3, 2) = m(2, 3);
		temp(2, 3) = m(3, 2);

		return temp;
	}
}
