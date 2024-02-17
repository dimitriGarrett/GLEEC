#pragma once

#include "PP/PP.h"
#include "PP/Compiler.h"

#include "string.h"

#include <array>
#include <utility>

namespace GLEEC::Internal::utility
{
    namespace detail
    {
        template <typename...>
        consteval const char* function_name()
        {
            return PP_CURRENT_FUNCTION;
        }

#if defined(__GNUC__) // gcc for sure works, but does clang?
        inline constexpr char START = '{';
        inline constexpr char END = '}';
#elif PP_COMPILER_MSVC
        inline constexpr char START = '<';
        inline constexpr char END = '>';
#endif

        consteval size_t length(const char* str)
        {
            return str[0] == '\0' ? 0 : length(str + 1) + 1;
        }

        consteval size_t find(const char* str, const char c)
        {
            for (size_t i = 0; i < length(str); ++i)
                if (str[i] == c) return i;
            return -1;
        }

        template <std::size_t F, typename... Ts, std::size_t... S>
        consteval std::array<char, sizeof...(S)> arr(std::index_sequence<S...>)
        {
            return { function_name<Ts...>()[F + S]... };
        }

        template <typename... Ts>
        consteval hash_t hash()
        {
            constexpr std::size_t l = 
                find(function_name<Ts...>(), END) - (find(function_name<Ts...>(), START) + 1);

            constexpr auto a = arr<find(function_name<Ts...>(), START) + 1, Ts...>
                (std::make_index_sequence<l>{});

            size_t result = FNVOffset;

            for (size_t i = 0; i < l; ++i)
            {
                result ^= a[i];
                result *= FNVPrime;
            }

            return result;
        }
    }

    template <typename... Ts>
    consteval hash_t type_hash()
    {
        return detail::hash<Ts...>();
    }
}
