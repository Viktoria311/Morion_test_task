#pragma once

#include <string>
#include <memory>
#include "CConfigSection.h"

class configparser {
private:
    std::unique_ptr<configsection> _section;

public:
    virtual ~configparser();

    template<typename T>
    int GetOption(const std::string& path) {
        return _section->GetOption<T>(path);
    } 
    bool operator!();

    friend bool fnApplySettings(const configparser& cfg);
};
