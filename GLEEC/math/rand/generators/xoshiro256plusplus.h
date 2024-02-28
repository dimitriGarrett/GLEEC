#pragma once

#include "splitmix64.h"

namespace GLEEC::math::rand
{
    struct xoshiro256plusplus
    {
        GLEEC_API static uint64_t next();
    };
}
