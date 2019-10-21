#pragma once
#include "Shader.h"
#include <unordered_map>
#include <typeindex>

template<typename t>
struct UniformInfo 
{
	t m_Type;
	std::string m_UniformName = "";
	unsigned int m_SizeOfName = 0;
	unsigned int m_Location = 0;
	std::string ToString() { return std::string("<Uniform: " + m_UniformName + "\n" + "Location: " + std::stoi(m_Location) + "\n" + "Type: " + typeid(t).name() + "> \n"); }
};



class Program 
{
public:
	void SetProgram(const unsigned int a_ProgramID) { m_ProgramID = a_ProgramID; }
	unsigned int GetProgram() const { return m_ProgramID; }
	template<typename t>
	void AddShader(t & a_Shader) { m_ShaderMap[typeid(a_Shader)] = a_Shader; }
	std::unordered_map<std::type_index, Shader>& GetMap();
private:
	unsigned int m_ProgramID;
	std::unordered_map<std::type_index, Shader> m_ShaderMap;
};

class ShaderManager 
{
public:
	static void CreateProgram(Program &a_Program);
	static void GetProgramInfo(Program &a_p);
private:
};