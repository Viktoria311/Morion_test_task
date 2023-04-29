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
protected:
	std::unordered_set<CConfigSection*> sections; // maybe unique_ptr
public:
	CFileConfig() : file_name(""), sections() {}
    CFileConfig(const std::string& file_name) : file_name(file_name), sections() {}
    CFileConfig(const CFileConfig& obj)
    {
        file_name = obj.file_name; // or SetFileName(obj.file_name);
        for (const auto& ptr : obj.sections)
        {
            // decltype and copy constructor of CConfigSection
            // auto* p_new_section = new CConfigSection(*ptr);
            auto* p_new_section = new CConfigSection(*ptr);

            sections.insert(p_new_section);
        }
        // have unordered_set<CConfigSection*>
    }
    virtual ~CFileConfig()
    {
        for (auto& ptr : sections)
        {
            delete ptr;
        }
    }
	virtual void Load(const std::string& str) = 0; // dynamic memory for sections
    void SetFileName(const std::string& str)
    {
        file_name = str;
    }

	CConfig* GetSection(const std::string& str) // virtual from CConfig
	{
		for (const auto& ptr_CConfigSection : sections)
		{
			if (ptr_CConfigSection->return_section_name() == str)
				return ptr_CConfigSection;
		}
	}

	operator bool() const
	{
        for(const auto& section_ptr : sections)
        {
            if (section_ptr == nullptr)
                return false;
            section_ptr->operator bool();
        }

        return true;
	}

	std::any GetOption(const std::string& str)
    {
        for(const auto& section : sections)
        {
            for(const auto& pair_key_val : section->RefSettings())
            {
                if (pair_key_val.first == str)
                    return pair_key_val.second;
            }
        }
    }
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
    void Load(); // for demonstration
    const std::unordered_map<std::string, std::any>& RefSettings() const override;
    std::unordered_map<std::string, std::any>& RefSettings() override;
};

class INIFileConfig : public CFileConfig
{
public:
	void Load(const std::string& str);
	
};