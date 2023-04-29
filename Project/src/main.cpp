#include <my_lib/CConfig.h>
#include <my_lib/CFileConfig.h>

#include <string>
#include <iostream>

void CoutAny(const std::any& option_value); // cout-helping func

int main() 
{
    JSONFileConfig json_file;

    // use polimorph member-func Load() for demonstration
    json_file.Load(); // json_file.Load("file path"); in real project
    auto p_section = json_file.GetSection("demonstration json section name");
    // "{\"project\":\"rapidjson\",\"stars\":10}";
    std::string searching_option = "stars";
    if (p_section->HasOption(searching_option))
    {
        auto option_value = p_section->GetOption(searching_option);

        std::cout << "Option with the key " << "\""<< searching_option << "\" : ";

        CoutAny(option_value);
    }
    else
        std::cout << "There is no options with the key " << "\""<< searching_option << "\" : "
                  << "in a \""<< p_section->return_section_name() << "\" section" << std::endl;

    std::cout << "Look at the section \" " << p_section->return_section_name() << " \""<< std::endl;
    for(const auto& pair_from_map : p_section->RefSettings()) // walking on the section`s map
    {
        try
        {
            std::cout << pair_from_map.first << " : ";

            CoutAny(pair_from_map.second);
        }
        catch(const std::bad_any_cast& e)
        {
            std::cerr << e.what() << '\n';
        }
    }


    //XMLFileConfig xml_file;       // without realization
    //xml_file.Load("file path");

    //INIFileConfig ini_file;       // without realization
    //ini_file.Load("file path");

    return 0;
}

void CoutAny(const std::any& option_value) // cout-helping func
{
    if (option_value.type() == typeid(int))
        std::cout << std::any_cast<int>(option_value);
    else if (option_value.type() ==  typeid(double))
        std::cout << std::any_cast<double>(option_value);
    else if (option_value.type() ==  typeid(float))
        std::cout << std::any_cast<float>(option_value);
    else if (option_value.type() == typeid(const char *))
        std::cout << std::any_cast<const char *>(option_value);
    else if (option_value.type() == typeid(std::string))
        std::cout << std::any_cast<std::string>(option_value);
    else
        std::cout << " has a difficult type";
    std::cout << std::endl;
}