#pragma once

#include <string>
#include <map>
#include <variant>


class CConfig // only interface
{
public:
	virtual CConfig* GetSection(const std::string& str) = 0;
	virtual ~CConfig();
	virtual operator bool() const = 0;
};



class CConfigSection : public CConfig // OR   public  CFileConfig
{
private:
	std::variant<bool, int, double, std::string> var;
	std::map<std::string, var> settings;
public:
	CConfigSection() : CConfig() { }


	CConfigSection* GetSection(const std::string& str);
	/*
	CConfigSection * sect = cfg.GetSection("App.Frames.RootFrame.Placement");
	*/

	/////////////////////////////////////////////////////////////////////////////////////
	bool SetOption(const std::string& str, int n)
	{
		// по какой причине может не установится опция под названием "ScreenPosX"  в указанное значение  ?


	}
	/*
	sect.SetOption("ScreenPosX", main_frame.x + 10);
	*/

	/////////////////////////////////////////////////////////////////////////////////////
	bool HasOption(const std::string& str);

	int GetOption(const std::string& str);
	/*
		main_frame.x = sect.GetOption("ScreenPosX");
        main_frame.Y = sect.GetOption("ScreenPosY");
        main_frame.Width = sect.GetOption("Width");
        main_frame.Height = sect.GetOption("Height");
	*/
	/////////////////////////////////////////////////////////////////////////////////////

	operator bool() const;
};


class CFileConfig : public CConfig
{
private:
	std::string file_name;
	CConfigSection* p_section;
public:
	CFileConfig() : file_name(""), p_section(nullptr) { }
	void Load(const std::string& str);
	/*
	CFileConfig cfg;
	cfg.Load("D:\CoolApp\Settings.dat");


	try-catch block for throw, when  there is no this file 
	*/
	operator bool() const
	{
		if (p_section == nullptr)
			return false;
		return true;
	}

};