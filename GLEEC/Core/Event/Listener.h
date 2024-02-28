#pragma once

#include "delegate.h"

namespace GLEEC::Event
{
    struct Listener
    {
        virtual ~Listener() = default;
    };

    template <typename... Args>
    struct Listenerer final : Listener
    {
        bool call(Args... args) const
        {
            return func(index, args...);
        }

        size_t index = 0;
        size_t priority = -1;

        delegate<bool(size_t, Args...)> func = nullptr;
    };
}
