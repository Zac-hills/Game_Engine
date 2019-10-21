#pragma once
#include <string>
#include <unordered_map>

class ScriptManager 
{
public:
	ScriptManager();
	~ScriptManager();
	//has to be absolute paths
	//D:\\Desktop\\Repositories\\ECS\\DrunkenInsomnia\\Bin\\VsDevCmd.bat", "cl /EHsc D:\\Desktop\\Repositories\\ECS\\DrunkenInsomnia\\Scripts\\TestScript.cpp
	static void CompileScript(std::string a_BatchFilePath, std::string a_ScriptPath);
	static bool NewScript(const std::string &a_ScriptName);
private:
	static std::string m_ScriptOutputDir;
	static std::unordered_map<std::string, unsigned int> m_ScriptMap;
	static std::string m_DefaultScript[30];
	static unsigned int ScriptID;
};

