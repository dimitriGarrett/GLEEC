#pragma once

#include "Internal/Localization/Language.h"
#include "Locale.h"

#include "Languages"
#include "Core/Config/Configuration.h"

namespace GLEEC::Localization
{
    struct LanguageManager
    {
        static void init()
        {
            Internal::Localization::Language::init();

            Internal::Localization::Language::loadLanguages(Config::Configuration::get("langs_dir"));
        }

        static void setCurrentLang(Internal::utility::hash_t key)
        {
            currentLang = key;
        }

        static Locale lang(Internal::utility::hash_t key)
        {
            return { key, Internal::Localization::Language::lang(key) };
        }

        static LangStringView get(Internal::utility::hash_t key)
        {
            return lang(currentLang).get(key);
        }

        static LangStringView get(Internal::utility::hash_t key, std::string_view name)
        {
            return lang(currentLang).get(key, name);
        }

        GLEEC_API static Internal::utility::hash_t currentLang;

        // lang(std::string_view) is not defined on purpose, same reason as locale get(std::string_view)
    };
}

#define TR(w) ::GLEEC::Localization::LanguageManager::get(::GLEEC::Internal::utility::hash(#w), #w)

#define LOCALE(l) ::GLEEC::Localization::LanguageManager::setCurrentLang(l)
