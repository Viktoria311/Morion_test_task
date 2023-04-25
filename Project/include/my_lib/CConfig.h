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
	std::unordered_map<std::string, std::any> settings;
public:
	CConfigSection() : CConfig() { }

	operator bool() const
	{
		if (settings.empty())
			return false;
		return true;
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
		return settings.contains(str);
	}

	std::any GetOption(const std::string& str)
	{
		return settings.at(str);
	}

};


