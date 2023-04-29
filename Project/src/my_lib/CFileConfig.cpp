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

void JSONFileConfig::Load() // for demonstration
{
    SetFileName("demonstration file path");
    std::string json = "{\"project\":\"rapidjson\",\"stars\":10}";

    rapidjson::Document doc;

    doc.Parse(json.c_str());

    // In JSONFileConfig there is  ONE   CConfigSection with big unordered_map
///*
 CConfigSection * p = new CConfigSection("demonstration json section name");

    for(auto it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
    {
        p->SetOption(it->name.GetString(), it->value.GetType()); // SetOption(const std::string& str, std::any n)
    }
    sections.insert(p);
 //*/

/*
    for(decltype(doc.MemberBegin()) it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
    {
        CConfigSection * p = new CConfigSection("section name");
        p->SetOption(it->name.GetString(), it->value.GetType()); // SetOption(const std::string& str, std::any n)
        sections.insert(p);
    }
*/
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

const std::unordered_map<std::string, std::any>& JSONFileConfig::RefSettings() const
{

    return (*(sections.cbegin()))->RefSettings();
}

std::unordered_map<std::string, std::any>& JSONFileConfig::RefSettings()
{
    return (*(sections.begin()))->RefSettings();
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