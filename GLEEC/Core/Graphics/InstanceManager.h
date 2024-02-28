#pragma once

#include "Instance.h"

namespace GLEEC::Graphics
{
    struct InstanceManager
    {
        GLEEC_API static void createInstance();
        GLEEC_API static void destroyInstance();

        GLEEC_API static Instance instance;
    };
}
