#pragma once

#include "delegate.h"

#include <vector>

namespace GLEEC::Internal::Event
{
    struct Listener
    {
        virtual ~Listener() = default;
    };

    template <typename... Args>
    struct Listenerer final : Listener
    {
        Listenerer() = default;
        Listenerer(size_t i, const delegate<bool(size_t, Args...)>& d)
            : index(i), func(d)
        {
        }

        bool call(Args... args) const
        {
            return func(index, args...);
        }

        size_t index = 0;
        delegate<bool(size_t, Args...)> func = nullptr;
    };
}
