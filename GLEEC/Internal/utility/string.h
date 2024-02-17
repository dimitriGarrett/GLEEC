#pragma once

#include "PP/Architecture.h"

namespace GLEEC::Internal::utility
{
	inline constexpr size_t npos = static_cast<size_t>(-1);

	template <typename char_type = char>
	constexpr size_t length(const char_type* str)
	{
		return str[0] == '\0' ? 0 : length(str + 1) + 1;
	}

	template <typename char_type = char>
	constexpr size_t find(const char_type* str, char_type ch)
	{
		for (size_t i = 0; i < length(str); ++i)
			if (ch == str[i]) return i;
		return npos;
	}

#if PP_ARCHITECTURE_64
	inline constexpr size_t FNVOffset = 0xcbf29ce484222325;
	inline constexpr size_t FNVPrime = 1099511628211;
#else
    inline constexpr size_t FNVOffset = 0x811x9dc5;
    inline constexpr size_t FNV_PRIME = 0x01000193;
#endif

	using hash_t = size_t;

	template <typename char_type = char>
	constexpr hash_t hash(const char_type* str)
	{
		size_t result = FNVOffset;

		for (size_t i = 0; i < length(str); ++i)
		{
			result ^= str[i];
			result *= FNVPrime;
		}

		return result;
	}
}
