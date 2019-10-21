#include <windows.h>
#include "ScriptManager.h"
#include <iostream>
#include <fstream>
#include <regex>


std::string GetCurrentWorkingDir() 
{
	char buff[FILENAME_MAX];
	GetCurrentDirectoryA(FILENAME_MAX, buff);
	std::string current_working_dir(buff);
	return current_working_dir;
}

std::unordered_map<std::string, unsigned int> ScriptManager::m_ScriptMap;

std::string ScriptManager::m_DefaultScript[30] =
{
 "#include <string>",
 "#include <typeinfo>",
 "#include \"BaseScript.h\"",
 "",
 "class ",/*insert 4-5 here*/ " : public BaseScript",
 "{",
 "public:",
 "	~",/*insert 8-9 here*/"() {}",
 "	void Start()",
 "  {", 
 "  }",
 "	void Update()",
 "  {",
 "  }",
 "",
 "	std::string ScriptName()",
 "	{",
 "		std::string Result(typeid(*this).name());",
 "		std::size_t pos = Result.find(" ");",
 "		Result = Result.substr(pos + 1);",
 "		return Result;",
 "	}",
 "};",
 "extern \"C\"",
 "{",
 "__declspec(dllexport) BaseScript * GetScript(){return new ", /*insert 25, 26 here*/
 "();}",
 "}"
};

unsigned int ScriptManager::ScriptID = 0;

ScriptManager::ScriptManager() {}
ScriptManager::~ScriptManager() {}

bool ScriptManager::NewScript(const std::string &a_ScriptName)
{
	auto iterator = m_ScriptMap.find(a_ScriptName);
	if (iterator == m_ScriptMap.end())
	{
		std::ofstream out(GetCurrentWorkingDir() + "\\" + "Scripts\\" + a_ScriptName + ".cpp");
		for (unsigned int i = 0; i < 30; i++)
		{
			if (i == 4 || i == 8 || i == 26)
			{
				out << m_DefaultScript[i] + a_ScriptName + m_DefaultScript[i + 1] << std::endl;
				++i;
				continue;
			}
			out << m_DefaultScript[i] << std::endl;
		}
		return true;
		m_ScriptMap[a_ScriptName] = ScriptID++;
	}

#ifdef _DEBUG
	std::cout << "Script Name already exists. \n";
#endif
	return false;
}

void ScriptManager::CompileScript(std::string a_BatchFilePath, std::string a_ScriptPath) 
{
	
}

