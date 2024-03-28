#pragma once

#include "Config/Export.h"

namespace GLEEC::Graphics
{
    struct Renderer
    {
        GLEEC_API static void init();
        GLEEC_API static void destroy();

        GLEEC_API static void begin();

        GLEEC_API static void draw();

        GLEEC_API static void end();
    };
}
