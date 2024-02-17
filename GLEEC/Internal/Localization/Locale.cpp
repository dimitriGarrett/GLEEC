#include "Locale.h"
#include "Config/Platform.h"

#if GLEEC_WINDOWS
#include <Windows.h>
#endif

namespace GLEEC::Internal::Localization
{
    int Locale::currentLang = EN;
    std::vector<std::unordered_map<LocaleKey, Translated>> Locale::locale = {};

    void Locale::init()
    {
        locale.resize(SP + 1);

        // to ensure utf8 output is received correctly
#if GLEEC_WINDOWS
        SetConsoleOutputCP(CP_UTF8);
#endif
    }
}
