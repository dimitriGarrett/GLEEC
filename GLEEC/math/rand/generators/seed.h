#pragma once

#include "Config/Export.h"
#include <cstdint>

namespace GLEEC::math::rand
{
    struct seed
    {
        GLEEC_API static uint64_t next();
    };
}
