#pragma once

#include "math/vec.h"
#include "math/utility/cseq.h"

#include <initializer_list>

namespace GLEEC::math
{
#define GLEEC_MATH_INTERNAL_MAT matrix<r, c, T>
#define GLEEC_MATH_INTERNAL_MAT_VARIADIC(dim, fun) [&]<length_t... N>(math::cseq<N...>) { fun }(math::make_cseq<dim>{})

	template <length_t Rows, length_t Columns, typename T>
	struct matrix
	{
		using vec_t = vec<Rows, T>;

		constexpr matrix() = default;

		template <typename T2>
		constexpr matrix(T2 scalar)
		{
			if constexpr (Rows == Columns)
			{
				[&] <length_t... N>(cseq<N...>) { ((data[N][N] = static_cast<T>(scalar)), ...); }(make_cseq<Rows>{});
			}

			else
			{
				[&] <length_t... N>(cseq<N...>) { ((data[N] = static_cast<T>(scalar)), ...); }(make_cseq<Rows * Columns>{});
			}
		}

		template <typename T2>
		constexpr matrix(std::initializer_list<T2> values)
		{
			length_t s = min(values.size(), Rows * Columns);
			if constexpr (Columns == Rows)
			{
				for (length_t i = 0; i < s; ++i)
				{
					operator() (i / Rows, i % Columns) = static_cast<T>(*(values.begin() + i));
				}
			}

			else
			{
				for (length_t i = 0; i < s; ++i)
				{
					data[i % Columns][i / Columns] = static_cast<T>(*(values.begin() + i));
				}
			}
		}

		template <typename T2>
		constexpr matrix(std::initializer_list<vec<Rows, T2>> vecs)
		{
			GLEEC_MATH_INTERNAL_MAT_VARIADIC
			(
				Rows,
				((data[N] = (*(vecs.begin() + N))), ...);
			);
		}

		/*template <length_t r, length_t c, typename T2>
		constexpr matrix(const matrix<r, c, T2>& rhs)
			requires (c >= Columns)
		{
			GLEEC_MATH_INTERNAL_MAT_VARIADIC
			(
				Rows,
				((data[N] = rhs[N]), ...);
			);
		}*/

		template <length_t r, length_t c, typename T2>
		constexpr matrix(const matrix<r, c, T2>& rhs)
			: matrix(static_cast<T>(1))
		{
			[&] <length_t... N>(cseq<N...>) { ((data[N] = rhs[N]), ...); }(make_cseq<(c > Columns ? Columns : c)>{});
		}

		static consteval length_t rows()
		{
			return Rows;
		}

		static consteval length_t columns()
		{
			return Columns;
		}

		constexpr vec<Columns, T> row(length_t index)
		{
            assert(index < Rows);

			vec<Columns, T> temp = {};
			[&] <length_t... N>(cseq<N...>) { ((temp[N] = data[index][N]), ...); }(make_cseq<Columns>{});
			return temp;
		}

		constexpr vec<Columns, T> row(length_t index) const
		{
			return const_cast<matrix*>(this)->row(index);
		}

		constexpr vec<Columns, T>& column(length_t index)
		{
			return operator[](index);
		}

		constexpr const vec<Columns, T>& column(length_t index) const
		{
			return operator[](index);
		}

		constexpr T& operator() (length_t row, length_t column)
		{
			assert(column < Columns);
			assert(row    < Rows);

			return data[column][row];
		}

		constexpr const T& operator() (length_t row, length_t column) const
		{
			return const_cast<matrix*>(this)->operator()(row, column);
		}

		constexpr vec_t& operator[] (length_t index)
		{
			assert(index < Columns);

			return data[index];
		}

		constexpr const vec_t& operator[] (length_t index) const
		{
			return const_cast<matrix*>(this)->operator[](index);
		}

	private:
		vec_t data[Columns] = { static_cast<T>(0) };
	};
}
