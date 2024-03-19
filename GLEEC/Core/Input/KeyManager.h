#pragma once

#include "Config/Export.h"
#include "Core/Input/Key.h"

#include <string_view>

namespace GLEEC::Input
{
    struct KeyManager
    {
        GLEEC_API static std::string_view keyName(Key key);
    };
}
