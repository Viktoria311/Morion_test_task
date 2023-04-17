#pragma once

#include "CConfig.h"
#include <memory>
#include <variant>
#include <unordered_map>
#include <string>


class file_config {
private:
    const std::string _path;
    configparser _parser;
public:
    void Load(const std::string& str);

    template<typename T>
    T GetOption(const std::string& path) {
        return _parser.template GetOption<T>(path);
    }
};

