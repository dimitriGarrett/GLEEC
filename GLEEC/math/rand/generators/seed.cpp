#include "seed.h"

#include <random>

namespace GLEEC::math::rand
{
    uint64_t seed::next()
    {
        static std::random_device r;
        static std::default_random_engine eng(r());
        static std::uniform_int_distribution<uint64_t> d;

        return d(r);
    }
}
