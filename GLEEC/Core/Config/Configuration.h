#pragma once

#include "Config/Export.h"
#include "Internal/utility/string.h"

#include "Internal/Log/Log.h"

#include <string>
#include <unordered_map>

namespace GLEEC::Config
{
    struct Configuration
    {
        static std::string_view get(Internal::utility::hash_t key)
        {
            if (config.contains(key))
            {
                return config.at(key);
            }

            LOG_WARNING("Attempted to access config parameter: {} but doesn't exist!", key);

            return (config[key] =
            std::format("Unknown Key {}!", key));
        }

        static std::string_view get(std::string_view name)
        {
            Internal::utility::hash_t key = Internal::utility::hash(name.data());
            
            if (config.contains(key))
            {
                return config.at(key);
            }

            LOG_WARNING("Attempted to access config parameter: {} but doesn't exist!", name);

            return (config[key] =
            std::format("Unknown Key {}!", name));
        }

        static const std::string& gets(Internal::utility::hash_t key)
        {
            if (config.contains(key))
            {
                return config.at(key);
            }

            LOG_WARNING("Attempted to access config parameter: {} but doesn't exist!", key);

            return (config[key] =
            std::format("Unknown Key {}!", key));
        }

        static const std::string& gets(std::string_view name)
        {
            Internal::utility::hash_t key = Internal::utility::hash(name.data());
            
            if (config.contains(key))
            {
                return config.at(key);
            }

            LOG_WARNING("Attempted to access config parameter: {} but doesn't exist!", name);

            return (config[key] =
            std::format("Unknown Key {}!", name));
        }

        static bool exists(Internal::utility::hash_t key)
        {
            return config.contains(key);
        }

        static bool exists(std::string_view name)
        {
            return exists(Internal::utility::hash(name.data()));
        }

        GLEEC_API static void init(std::string_view filepath);
        GLEEC_API static void init();

        GLEEC_API static std::unordered_map<Internal::utility::hash_t, std::string> config;
    };
}
