#pragma once

#include "default_t"

#include "Internal/Log/Log.h"

namespace GLEEC
{
    inline void printInitString()
    {
        // TODO: for each internal module print its initString

        // for now there is only the default
        LOG_INFO("{}",
            (sizeof(default_t) == sizeof(double) ?
            "GLEEC x64" :
            "GLEEC x86"));
    }
}
