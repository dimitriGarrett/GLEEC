#include "Directory.h"

#include <filesystem>

namespace GLEEC::Internal::Config
{
    std::string GLEECDirectory()
    {
        std::string executable = std::filesystem::current_path().string();

        return executable.substr(0, executable.find("GLEEC") + 5) + "/"; // include the slash
    }
}
