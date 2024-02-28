#pragma once

namespace GLEEC::Internal::utility
{
    namespace detail
    {
        template <typename T, typename = void()>
        struct is_callable
        {
            static constexpr bool value = false;
        };

        template <typename T>
        struct is_callable<T, decltype(&T::operator())>
        {
            static constexpr bool value = true;
        };
    }

    template <typename T>
    inline constexpr bool is_callable = detail::is_callable<T>::value;
}
