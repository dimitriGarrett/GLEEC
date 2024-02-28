#pragma once

#include "Clock.h"

namespace GLEEC::Internal::Time
{
    inline uint64_t now()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}
