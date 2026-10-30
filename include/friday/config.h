// FRIDAY AI — Configuration module declarations
#pragma once

#include <string>
#include <map>

namespace friday
{

    class Config
    {
    public:
        // Loads configuration from a file.
        // Missing keys will use default values.
        void load(const std::string &filepath);

        // Gets a config value by key.
        // Returns default_value if key is not found.
        std::string get(const std::string &key,
                        const std::string &default_value = "") const;

    private:
        std::map<std::string, std::string> values_;

        void setDefaults();
    };

} // namespace friday