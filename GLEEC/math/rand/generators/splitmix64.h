#pragma once

#include "seed.h"

namespace GLEEC::math::rand
{
    struct splitmix64
    {
        GLEEC_API static uint64_t next();
    };
}
