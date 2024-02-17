#include "Locale.h"

#include <fstream>

namespace GLEEC::Internal::Localization
{
    void Locale::load(std::string_view filepath)
    {
        std::ifstream file(filepath.data());

        if (!file.is_open())
        {
            LOG_WARNING("Language file: {}, was not found!", filepath); return;
        }

        std::string line = "";

        std::string key = "";
        std::string translated = "";
        while (std::getline(file, line))
        {
            key = line.substr(0, line.find(':'));

            size_t first = line.find_first_of('\"');
            translated = line.substr(first + 1, line.find_last_of('\"') - first - 1);

            strings[utility::hash(key.c_str())] = translated;
        }
    }
}
