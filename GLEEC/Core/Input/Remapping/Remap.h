#pragma once

#include "RemapState.h"

namespace GLEEC::Input
{
    struct Remap
    {
        RemapState from = {};
        RemapState to = {};
    };
}
