#include <my_lib/CFileConfig.h>
#include <string>
#include <unordered_set>
#include <any>
#include <fstream>
#include <iostream>
#include <utility>
#include <exception>

#include <rapidxml/rapidxml.hpp>

#include <rapidjson/document.h>
#include <rapidjson/reader.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/error/en.h>
#include <mmcobj.h>


void XMLFileConfig::Load(const std::string& str)
{
    SetFileName(str);

    // read all file in one string
    std::ifstream file(str);

    std::string helping_str;
    std::string xml;

    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, helping_str);
            xml += helping_str;
        }
        // having xml string

        // code of filling fields of class
    }

}

void JSONFileConfig::Load(const std::string& str)
{
    //using namespace rapidjson;

    SetFileName(str);
    std::ifstream file(str);

    // read all file in one string
    std::string helping_str;
    std::string json;

    if (file.is_open())
    {
        while( !file.eof() )
        {
            getline(file, helping_str);
            json += helping_str;
        }
        // having json string
        rapidjson::Document doc;

        doc.Parse(json.c_str());

        // In JSONFileConfig there is  ONE   CConfigSection with big unordered_map

        CConfigSection * p = new CConfigSection();

        for(decltype(doc.MemberBegin()) it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
        {
            p->SetOption(it->name.GetString(), it->value.GetType()); // SetOption(const std::string& str, std::any n)
        }
        sections.insert(p);

    }
}




void INIFileConfig::Load(const std::string& str)
{
    SetFileName(str);

    std::ifstream file(str);
    // read all file in one string
    std::string helping_str;
    std::string ini;

    if (file.is_open())
    {
        while( !file.eof() )
        {
            getline(file, helping_str);
            ini += helping_str;
        }
        // having ini string

        // code of filling fields of class
    }
}