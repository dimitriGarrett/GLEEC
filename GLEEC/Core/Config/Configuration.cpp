#include "Configuration.h"
#include "Internal/Config/Directory.h"

#include <fstream>

namespace GLEEC::Config
{
    std::unordered_map<Internal::utility::hash_t, std::string> Configuration::config = {};

    void Configuration::init(std::string_view filepath)
    {
        if (!exists("cwd"))
        {
            // cwd is inferred from the executable location
            config[Internal::utility::hash("cwd")] = Internal::Config::GLEECDirectory();
        }
        
        LOG_INFO("cwd: {}", get("cwd"));

        std::ifstream file(filepath.data());

        if (!file.is_open())
        {
            LOG_WARNING("Config file: {}, was not found!", filepath); return;
        }

        std::string line = "";
        while (std::getline(file, line))
        {
            std::string var = line.substr(0, line.find_first_of(' '));
            std::string val = line.substr(line.find('=') + 2);

            Internal::utility::hash_t key = Internal::utility::hash(var.c_str());

            // if it is a compound statement
            if (val.find('+') != std::string::npos)
            {
                std::string lhs = val.substr(0, val.find_first_of(' '));
                std::string rhs = val.substr(val.find_last_of(' ') + 1);

                if (exists(lhs) && exists(rhs))
                {
                    config[key] = gets(lhs) + gets(rhs);
                }

                else if (exists(lhs) && !exists(rhs))
                {
                    config[key] = gets(lhs) + rhs;
                }

                else if (!exists(lhs) && exists(rhs))
                {
                    config[key] = lhs + gets(rhs);
                }

                // why would this ever happen? not sure.
                else
                {
                    config[key] = lhs + rhs;
                }
            }

            else
            {
                config[key] = val;
            }
        }
    }

    void Configuration::init()
    {
        // cwd is inferred from the executable location
        config[Internal::utility::hash("cwd")] =
            Internal::Config::GLEECDirectory();

        // if no config file provided, assume the default location is cwd + /config.txt (which it should be with the current filesystem layout)
        return init(std::string(get("cwd")) + std::string("config.txt"));
    }
}
