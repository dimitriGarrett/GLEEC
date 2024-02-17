#pragma once

#include "Config/Export.h"

#include "Translated.h"
#include "Languages"
#include "LOCSTR.h"

#include <vector>
#include <unordered_map>

namespace GLEEC::Internal::Localization
{
    using LocaleKey = utility::hash_t;

    struct Locale
    {
        GLEEC_API static void init();

        static void setLang(int lang)
        {
            currentLang = lang;
        }

        static std::string getString(LocaleKey phrase)
        {
            return locale[currentLang][phrase].str;
        }

        static void setString(int lang, LocaleKey phrase, std::string string)
        {
            locale[lang][phrase].str = string;
        }

        GLEEC_API static int currentLang;
        GLEEC_API static std::vector<std::unordered_map<LocaleKey, Translated>> locale;
    };
}

#define LOCALIZE(lang, phrase, str) ::GLEEC::Internal::Localization::Locale::setString(lang, LOCSTR(phrase), str)
#define LOCALIZED(phrase) ::GLEEC::Internal::Localization::Locale::getString(LOCSTR(phrase))

#define LOCALIZE_EN(phrase, str) LOCALIZE(EN, phrase, str)
#define LOCALIZE_SP(phrase, str) LOCALIZE(SP, phrase, str)

#define LOCALE(lang) ::GLEEC::Internal::Localization::Locale::setLang(lang)

#define LOCALE_EN() LOCALE(EN)
#define LOCALE_SP() LOCALE(SP)
