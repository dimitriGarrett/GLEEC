#pragma once

#include <vector>
#include <cstdint>

namespace GLEEC::Audio
{
    struct SoundInfo
    {
        std::vector<short> data = {};

        uint8_t channels = static_cast<uint8_t>(-1);
        int32_t sampleRate = -1;
    };
}
