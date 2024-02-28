#include "xoshiro256plusplus.h"

#include "rotl.h"

namespace GLEEC::math::rand
{
    uint64_t xoshiro256plusplus::next()
    {
        // recommended by creators of xoshiro
        static uint64_t seed[4] =
        {
            splitmix64::next(),
            splitmix64::next(),
            splitmix64::next(),
            splitmix64::next(),
        };

        const uint64_t result = rotl(seed[0] + seed[3], 23) + seed[0];
        const uint64_t t = seed[1] << 17;

        seed[2] ^= seed[0];
        seed[3] ^= seed[1];
        seed[1] ^= seed[2];
        seed[0] ^= seed[3];

        seed[2] ^= t;

        seed[3] = rotl(seed[3], 45);

        return result;
    }
}
