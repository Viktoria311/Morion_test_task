#include "CConfigSection.h"
#include <string>
#include <iostream>
#include <vector>


int main() {
    configsection root;
    configsection db_section;
    configsection db_options_section;

    db_options_section.SetOption("TTL", 1.5f);
    db_section.SetOption("HostName", std::string("localhost"));
    db_section.SetOption("Port", 1234);
    db_section.SetOption("Options", db_options_section);
    root.SetOption("Protocol", std::string("tcp"));
    root.SetOption("DB", db_section);

    std::cout << db_section.GetOption<std::string>("HostName") << '\n';
    std::cout << root.GetOption<std::string>("DB.HostName") << '\n';

    auto result_section = root.get_section("DB.Options");

    std::cout << result_section.GetOption<float>("TTL");
}




