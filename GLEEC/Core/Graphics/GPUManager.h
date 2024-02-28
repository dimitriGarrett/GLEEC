#pragma once

#include "GPU.h"

namespace GLEEC::Graphics
{
    struct GPUManager
    {
        GLEEC_API static void selectGPU();
        GLEEC_API static void closeGPU();

        GLEEC_API static GPU activeGPU;
    };
}
