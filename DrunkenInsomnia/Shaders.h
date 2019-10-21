#pragma once
#include<string>

class Shader 
{
public:
	Shader();
	~Shader();

private:
	std::string m_FilePath;
	unsigned int m_ShaderID;

};