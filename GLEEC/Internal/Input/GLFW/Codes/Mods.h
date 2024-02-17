#pragma once

#include <cstdint>

namespace GLEEC
{
    enum Mods : int32_t
    {
		MODIFIER_SHIFT = 0x0001,
		MODIFIER_CONTROL = 0x0002,
		MODIFIER_ALT = 0x0004,
		MODIFIER_SUPER = 0x0008,
		MODIFIER_CAPS_LOCK = 0x0010,
		MODIFIER_NUM_LOCK = 0x0020,
    };
}
