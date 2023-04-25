#pragma once

#include "CConfig.h"
#include <string>
//#include <unordered_map>
#include <unordered_set>
#include <any>



class CFileConfig : public CConfig
{
private:
	std::string file_name;
	std::unordered_set<CConfigSection*> sections;
public:
	CFileConfig() : file_name(""), sections() {}
	virtual void Load(const std::string& str) = 0;
    void SetFileName(const std::string& str)
    {
        file_name = str;
    }
	CConfig* GetSection(const std::string& str) // virtual от CConfig
	{
		for (const auto& ptr_CConfigSection : sections)
		{
			if (ptr_CConfigSection->return_section_name() == str)
				return ptr_CConfigSection;
		}
	}

	operator bool() const
	{
		return true;
	}

	std::any GetOption(const std::string& str);
};




class XMLFileConfig : public CFileConfig
{
public:
	void Load(const std::string& str);
};

class JSONFileConfig : public CFileConfig
{
public:
	void Load(const std::string& str);
};

class INIFileConfig : public CFileConfig
{
public:
	void Load(const std::string& str);
	
};