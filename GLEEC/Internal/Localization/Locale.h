#pragma once

#include "Config/Export.h"
#include "LangString.h"

#include "Internal/utility/string.h"

#include <string_view>
#include <unordered_map>

#include "Internal/Log/Log.h"

namespace GLEEC::Internal::Localization
{
    struct Locale
    {
        std::unordered_map<utility::hash_t, LangString> strings = {};

        LangStringView get(utility::hash_t key)
        {
            if (strings.contains(key))
            {
                return strings.at(key);
            }

            LOG_WARNING("Attempted to access Locale string: {}, but it doesn't exist!", key);

            return (strings[key] =
            std::format("Unknown Translation Key: {}!", key));
        }

        LangStringView get(std::string_view name)
        {
            utility::hash_t key = utility::hash(name.data());

            if (strings.contains(key))
            {
                return strings.at(key);
            }

            LOG_WARNING("Attempted to access Locale string: {}, but it doesn't exist!", name);

            return (strings[key] =
            std::format("Unknown Translation Key: {}!", name));
        }

        LangStringView get(utility::hash_t key, std::string_view name)
        {
            if (strings.contains(key))
            {
                return strings.at(key);
            }

            LOG_WARNING("Attempted to access Locale string: {}, but it doesn't exist!", name);

            return (strings[key] =
            std::format("Unknown Translation Key: {}!", name));
        }

        GLEEC_API void load(std::string_view filepath);
    };
}
