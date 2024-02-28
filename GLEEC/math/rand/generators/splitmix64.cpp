#include "splitmix64.h"

namespace GLEEC::math::rand
{
    uint64_t splitmix64::next()
    {
        static uint64_t seed = seed::next();

        uint64_t z = (seed += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
}
