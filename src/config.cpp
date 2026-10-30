// FRIDAY AI — Configuration module implementation

#include "friday/config.h"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace friday
{

    void Config::setDefaults()
    {
        values_["assistant_name"] = "FRIDAY";
        values_["version"] = "0.1.0";
        values_["greeting"] = "Hello! I am your personal assistant.";
        values_["prompt_symbol"] = "friday>";
    }

    void Config::load(const std::string &filepath)
    {
        // Start with defaults
        setDefaults();

        // If config file doesn't exist, just use defaults
        if (!std::filesystem::exists(filepath))
        {
            std::cout << "[Config] No config file found. Using defaults.\n\n";
            return;
        }

        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cout << "[Config] Warning: Could not open " << filepath
                      << ". Using defaults.\n\n";
            return;
        }

        int loaded = 0;
        std::string line;
        while (std::getline(file, line))
        {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            // Find the '=' separator
            size_t pos = line.find('=');
            if (pos == std::string::npos)
            {
                continue; // No '=' found, skip this line
            }

            // Extract key and value
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Store in map (overwrites default if key exists)
            values_[key] = value;
            ++loaded;
        }

        std::cout << "[Config] Loaded " << loaded << " settings from "
                  << filepath << ".\n\n";
    }

    std::string Config::get(const std::string &key,
                            const std::string &default_value) const
    {
        auto it = values_.find(key);
        if (it != values_.end())
        {
            return it->second;
        }
        return default_value;
    }

} // namespace friday