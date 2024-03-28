#pragma once

#include "Config/Export.h"

#include "Internal/Time/Time.h"

namespace GLEEC::Time
{
    using Timepoint = Internal::Time::Timepoint;

    struct TimeManager
    {
        GLEEC_API static uint64_t frameCount;

        GLEEC_API static double fps;
        GLEEC_API static double dt;

        static constexpr double fpsFixed = 60.0;
        static constexpr double dtFixed = (1.0 / fpsFixed);

        GLEEC_API static uint64_t now();
        GLEEC_API static void update();

        GLEEC_API static Timepoint localTime();
        GLEEC_API static Timepoint utcTime();
        GLEEC_API static Timepoint gmtTime();
    };
}
