#pragma once

#include <cstdint>

namespace GLEEC::Internal::Image
{
    struct Image
    {
        unsigned char* data = nullptr;

        // msvc isnt happy when i dont have static casts :(

        uint32_t width = static_cast<uint32_t>(-1);
        uint32_t height = static_cast<uint32_t>(-1);

        uint8_t channels = static_cast<uint8_t>(-1);
    };
}
