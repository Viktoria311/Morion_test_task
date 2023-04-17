#pragma once

//#include "CConfig.h"
//#include "CFileConfig.h"
#include <memory>
#include <variant>
#include <unordered_map>
#include <string>

class configsection {
    typedef std::variant<std::string, bool, int, float> value_t;
    typedef std::unordered_map<std::string, value_t> config_section_t;

    config_section_t _sections{};

public:
    configsection() = default;

    template<typename T>
    configsection(std::string k, T value) {
        _sections = config_section_t(value);
    }


    template<typename T>
    T GetOption(const std::string& path) {
        return std::get<T>(_sections.at(path));
    }

    template<typename T>
    bool SetOption(std::string path, T value) {
        auto [_, inserted] = (_sections.emplace(path, value));
        return inserted;
    }

    bool SetOption(const std::string& path, const configsection& value) {
        try {
            for (auto [kkey, kvalue] : value._sections) {
                _sections.emplace(path + "." + kkey, std::move(kvalue));
            }
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }

    configsection get_section(const std::string& path) {
        configsection section;
        for (auto [kkey, kvalue] : _sections) {
            if (kkey.rfind(path) == 0) {
                section.SetOption(kkey.substr(path.length() + 1), kvalue);
            }
        }
        return section;
    }

    bool HasOption(const std::string& str);

    bool HasOption(const std::list<std::string>& str);
};