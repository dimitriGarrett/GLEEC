#include "Language.h"
#include "Internal/Log/Log.h"

#include <filesystem>

#if GLEEC_WINDOWS
#include <Windows.h>
#endif

namespace GLEEC::Internal::Localization
{
    std::unordered_map<utility::hash_t, Locale> Language::languages = {};

    void Language::init()
    {
        // ensures UTF-8 output in the console, is this useful for games where console is ignored? not sure. TODO: maybe remove
#if GLEEC_WINDOWS
        SetConsoleOutputCP(CP_UTF8);
#endif
    }

    void Language::loadLanguages(std::string_view directory)
    {
        for (const auto& file : std::filesystem::directory_iterator(directory.data()))
        {
            const std::string lang_file = file.path().string();

            size_t dot = lang_file.find('.') - 2;

            const std::string lang = lang_file.substr(dot, 2);

            languages[utility::hash(lang.c_str())].load(file.path().string());

            LOG_INFO("Loaded language file: {}", lang_file);
            LOG_INFO("Loaded language: {}", lang);
        }
    }
}
