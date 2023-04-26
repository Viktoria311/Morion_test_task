#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <any>


class CConfig // only interface
{
public:
	virtual CConfig* GetSection(const std::string& str) = 0;
	virtual ~CConfig();
	virtual operator bool() const = 0;
};



class CConfigSection : public CConfig
{
private:
	std::string section_name;
protected:
	std::unordered_map<std::string, std::any> settings;
public:
	CConfigSection() : section_name(""), settings() { }

    std::unordered_map<std::string, std::any>& RefSettings()
    {
        return settings;
    }

	operator bool() const
	{
        // if unordered_map isn`t empty and there ate all values return true
		if (settings.empty())
			return false;
        for(const auto& setting_pair: settings)
        {
            if (!setting_pair.second.has_value())
                return false;
        }
		return true;
	}
    CConfig* GetSection(const std::string& str)
    {
        if (section_name == str)
            return this;
        return nullptr;
    }

	const std::string& return_section_name() const
	{
		return section_name;
	}


	bool SetOption(const std::string& str, std::any n)
	{
		return (settings.insert({ str, n })).second;
	}

	bool HasOption(const std::string& str)
	{
		return settings.contains(str); // C++20
	}

	std::any GetOption(const std::string& str)
	{
		return settings.at(str);
	}

};
