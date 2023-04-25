#include <my_lib/CFileConfig.h>
#include <string>
#include <unordered_set>
#include <any>
#include <fstream>
#include <iostream>
#include <exception>

#include <rapidxml/rapidxml.hpp>

#include <rapidjson/reader.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/error/en.h>


void XMLFileConfig::Load(const std::string& str)
{

}

void JSONFileConfig::Load(const std::string& str)
{
    using namespace rapidjson;

    SetFileName(str);
    std::ifstream file(str);


    if (file.is_open())
    {

    }

}

void INIFileConfig::Load(const std::string& str)
{

}