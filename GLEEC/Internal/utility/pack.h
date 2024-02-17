#pragma once

#include <stddef.h>

namespace GLEEC::Internal::utility
{
    namespace detail
    {
        /*
           All of this jumping around is necessary for empty packs,
           which just returns void if the pack is empty
        */

        template <size_t N, typename Arg, typename... Args>
        struct nth_type_impl_impl
        {
            using type = typename nth_type_impl_impl<N - 1, Args...>::type;
        };

        template <typename Arg, typename... Args>
        struct nth_type_impl_impl<0, Arg, Args...>
        {
            using type = Arg;
        };

        template <size_t N, typename... Args>
        struct nth_type_finder
        {
            using type = typename nth_type_impl_impl<N, Args...>::type;
        };

        template <size_t N>
        struct nth_type_finder<N> // specialize for empty pack
        {
            using type = void;
        };

        template <size_t N, typename... Args>
        struct nth_type_impl
        {
            using type = nth_type_finder<N, Args...>::type;
        };
    }

    template <size_t N, typename... Args>
    using nth_type = detail::nth_type_impl<N, Args...>::type;

    template <typename... Args>
    using first_type = nth_type<0, Args...>;

    template <typename... Args>
    using last_type = nth_type<sizeof...(Args) - 1, Args...>;
}
