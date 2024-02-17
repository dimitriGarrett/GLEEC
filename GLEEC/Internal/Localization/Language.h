#pragma once

#include "Locale.h"

namespace GLEEC::Internal::Localization
{
    struct Language
    {
        GLEEC_API static void loadLanguages(std::string_view directory);

        static Locale& lang(utility::hash_t hash)
        {
            if (languages.contains(hash))
            {
                return languages.at(hash);
            }

            LOG_WARNING("Attempted to access language: {}, but it doesn't exist!", hash);

            return languages[hash];
        }

        static Locale& lang(std::string_view name)
        {
            utility::hash_t hash = utility::hash(name.data());

            if (languages.contains(hash))
            {
                return languages.at(hash);
            }

            LOG_WARNING("Attempted to access language: {}, but it doesn't exist!", name);

            return languages[hash];
        }

        static Locale& lang(utility::hash_t hash, std::string_view name)
        {
            if (languages.contains(hash))
            {
                return languages.at(hash);
            }

            LOG_WARNING("Attempted to access language: {}, but it doesn't exist!", name);

            return languages[hash];
        }

        GLEEC_API static void init();

        // indexed by lowercase 2 letter language (en -> 0)
        // this is loaded at runtime and shouldn't be hardcoded, just to allow
        // more flexibility in the language loading and ease of localization 
        GLEEC_API static std::unordered_map<utility::hash_t, Locale> languages;
    };
}
