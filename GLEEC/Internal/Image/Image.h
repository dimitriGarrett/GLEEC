#pragma once

#include <cstdint>

namespace GLEEC::Internal::Image
{
    struct Image
    {
        unsigned char* data = nullptr;

        uint32_t width = -1;
        uint32_t height = -1;

        uint8_t channels = -1;
    };
}
