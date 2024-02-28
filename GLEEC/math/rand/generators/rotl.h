#pragma once

#include <cstdint>

namespace GLEEC::math::rand
{
    inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }
}
