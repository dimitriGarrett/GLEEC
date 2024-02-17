#pragma once

#include "length_t.h"

namespace GLEEC::math
{
	template <length_t... Ds>
	struct cseq
	{
		static consteval length_t size()
		{
			return sizeof...(Ds);
		}
	};

	namespace detail
	{
		template <length_t N, length_t... Args>
		struct make_cseq
		{
			using type = make_cseq<N - 1, N, Args...>::type;
		};

		template <length_t... Args>
		struct make_cseq<0, Args...>
		{
			using type = cseq<0, Args...>;
		};
	}

	template <length_t N>
	using make_cseq = typename detail::make_cseq<N - 1>::type;
}
