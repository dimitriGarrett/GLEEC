#include "TimeManager.h"

namespace GLEEC::Time
{
    uint64_t TimeManager::frameCount = 0;

    double TimeManager::fps = 0.0;
    double TimeManager::dt = 0.0;

    inline uint64_t TimeManager::now()
    {
        return Internal::Time::now();
    }

    inline void TimeManager::update()
    {
        static double lastTime = now();

        dt = now() - lastTime;
        fps = 1.0 / dt;

        ++frameCount;
    }

    inline Timepoint TimeManager::localTime()
    {
        return Internal::Time::LocalTime::current();
    }

    inline Timepoint TimeManager::utcTime()
    {
        return Internal::Time::UtcTime::current();
    }

    inline Timepoint TimeManager::gmtTime()
    {
        return utcTime();
    }
}
