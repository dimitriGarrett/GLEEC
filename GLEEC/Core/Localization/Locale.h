#pragma once

#include "Internal/Localization/Locale.h"
#include "LangString.h"

namespace GLEEC::Localization
{
    struct Locale
    {
        Internal::utility::hash_t language = {};

        LangStringView get(Internal::utility::hash_t key)
        {
            return locale.get(key);
        }

        LangStringView get(Internal::utility::hash_t key, std::string_view name)
        {
            return locale.get(key, name);
        }

        // get(std::string_view name) is intentially not implemented
        // because only macros should be used with core, so hashing is not
        // done at runtime, but compile time

        Internal::Localization::Locale& locale;
    };
}
