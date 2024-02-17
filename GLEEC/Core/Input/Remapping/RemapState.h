#pragma once

#include <cstdint>
#include <unordered_map>

namespace GLEEC::Input
{
    using Modifiers = uint32_t;

    struct RemapState
    {
        Modifiers mods = {};
        uint32_t state = static_cast<uint32_t>(-1); // key/mouse/gamepad

        RemapState(Modifiers mod, uint32_t State)
            : mods(mod), state(State)
        {
        }

        RemapState(int32_t Mods, int32_t State)
            : mods(static_cast<Modifiers>(Mods)),
              state(static_cast<uint32_t>(State))
        {
        }

        RemapState() = default;

        bool operator== (const RemapState&) const = default;
        bool operator!= (const RemapState&) const = default;
    };
}

namespace std
{
    template <>
    struct hash<::GLEEC::Input::RemapState>
    {
        size_t operator() (const ::GLEEC::Input::RemapState state) const
        {
            uint64_t n = (state.mods << 31) | (state.state);
            return std::hash<uint64_t>{}(n);
        }
    };
}
