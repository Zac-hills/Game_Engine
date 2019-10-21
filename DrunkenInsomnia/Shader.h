#pragma once
#include <string>


class Shader 
{
public:
	Shader() {}
	~Shader() {}
	void SetID(const unsigned int a_ID) { m_ShaderID = a_ID; }
	void SetFilePath(const std::string &a_FilePath) { m_FilePath = a_FilePath; }
	unsigned int GetID() const { return m_ShaderID; }
	std::string GetFilePath() { return m_FilePath; }
	void SetFile(const std::string &a_RawFile) { m_RawFile = a_RawFile; }
	std::string& GetRawFile() { return m_RawFile; }
private:
	std::string m_FilePath;
	unsigned int m_ShaderID;
	std::string m_RawFile;
};

class VertexShader : public Shader 
{
public:
	VertexShader() {};
	~VertexShader() {};
};

class FragmentShader : public Shader 
{
public:
	FragmentShader() {};
	~FragmentShader() {};
};

class GeometryShader : public Shader 
{
public:
	GeometryShader() {}
	~GeometryShader() {}
};

class TessellationShader : public Shader 
{
public:
	TessellationShader() {}
	~TessellationShader() {}
};