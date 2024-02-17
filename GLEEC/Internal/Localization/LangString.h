#pragma once

#include <string>

namespace GLEEC::Internal::Localization
{
    // this only exists to possibly replace the string type if needed in the future
    using LangString = std::string;
    using LangStringView = std::string_view;
}
