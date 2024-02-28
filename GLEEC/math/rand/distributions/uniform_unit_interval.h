#pragma once

#include <cstdint>

#include "Config/default_t"

namespace GLEEC::math::rand
{
    // [0, 1)
    struct uniform_unit_interval
    {
        template <typename gen>
        static double generated()
        {
            return (gen::next() >> 11) * 0x1.0p-53;
        }

        template <typename gen>
        static float generatef()
        {
            return static_cast<float>(generated<gen>());
        }

        template <typename gen>
        static default_t generate()
        {
            if constexpr (sizeof(default_t) == sizeof(double))
                return generated<gen>();
            else if constexpr (sizeof(default_t) == sizeof(float))
                return generatef<gen>();
            return static_cast<default_t>(generated<gen>());
        }
    };
}
