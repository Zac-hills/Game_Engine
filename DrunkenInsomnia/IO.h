#pragma once
#include "GL\glew.h"
#include "Images.h"
#include <iostream>
#include "Shader.h"
#include <fstream>
#include <string>
#include <vector>
#include "Text.h"
#include "File.h"

void PrintLine(std::string s)
{
	std::cout << s << std::endl;
}

FREE_IMAGE_FORMAT CheckType(const std::string &a_FilePath) 
{
	FREE_IMAGE_FORMAT f = FIF_UNKNOWN;
	f = FreeImage_GetFileType(a_FilePath.c_str(), 0);
	PrintLine("Getting File Type.");

	if (f == FIF_UNKNOWN)
	{
		f = FreeImage_GetFIFFromFilename(a_FilePath.c_str());
		PrintLine("Getting File type from File Name.");
		if (f == FIF_UNKNOWN)
		{
			PrintLine("Cant figure out the type of the image.");
		}
	}

	return f;
}

template<typename T>
T Load(const std::string &a_FilePath) 
{
	return T;
};


template<>
Image Load<Image>(const std::string &a_FilePath)
{
	FIBITMAP *l_Image;
	Image l_Result;
	l_Result.m_FilePath = a_FilePath;
	l_Result.m_FileType = CheckType(l_Result.m_FilePath);
	l_Image = FreeImage_Load(l_Result.m_FileType, l_Result.m_FilePath.c_str());
	l_Result.m_Height = FreeImage_GetHeight(l_Image);
	l_Result.m_Width = FreeImage_GetWidth(l_Image);
	l_Result.m_Depth = FreeImage_GetBPP(l_Image) / 8;
	l_Result.m_Bits = new BYTE[l_Result.m_Height * l_Result.m_Width * l_Result.m_Depth];
	PrintLine(l_Result.ToString());
	std::memcpy(l_Result.m_Bits, FreeImage_GetBits(FreeImage_ConvertTo32Bits(l_Image)), l_Result.m_Height * l_Result.m_Width * l_Result.m_Depth);
	FreeImage_Unload(l_Image);
	return l_Result;
}

bool compileShader(unsigned int shader_ptr)
{
	glCompileShader(shader_ptr);

	GLint success;

	glGetShaderiv(shader_ptr, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<>
VertexShader Load<VertexShader>(const std::string &a_FilePath) 
{
	std::string Path = "./Shaders/VertexShader/";
	VertexShader l_Result;
	//creating objects/variables
	l_Result.SetID(glCreateShader(GL_VERTEX_SHADER));
	l_Result.SetFilePath(a_FilePath);
	//read shader

		File file(Path + a_FilePath);
		if (!file.open("rb")) 
		{
			std::cout << "File Could Not Load \n";
		}
		l_Result.SetFile(std::string(file.getContents()));
		file.close();

	const char *const shaderCode = l_Result.GetRawFile().c_str();
	std::cout << l_Result.GetRawFile().c_str();
	//creating shader source
	glShaderSource(l_Result.GetID(), 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(l_Result.GetID()))
	{
		std::cout << "Vertex shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Vertex Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(l_Result.GetID(), GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(l_Result.GetID(), sizeof(char) * 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
	return l_Result;
}

template<>
FragmentShader Load<FragmentShader>(const std::string &a_FilePath)
{
	std::string Path = "./Shaders/FragmentShader/";
	FragmentShader l_Result;
	//creating objects/variables
	l_Result.SetID(glCreateShader(GL_FRAGMENT_SHADER));
	l_Result.SetFilePath(a_FilePath);
	//read shader
	File file(Path + a_FilePath);
	if (!file.open("rb"))
	{
		std::cout << "File Could Not Load \n";
	}
	l_Result.SetFile(std::string(file.getContents()));
	file.close();
	const char *shaderCode = l_Result.GetRawFile().c_str();
	//creating shader source
	glShaderSource(l_Result.GetID(), 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(l_Result.GetID()))
	{
		std::cout << "Fragment shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Fragment Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(l_Result.GetID(), GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(l_Result.GetID(), sizeof(char) * 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
	return l_Result;
}

template<>
GeometryShader Load<GeometryShader>(const std::string &a_FilePath)
{
	GeometryShader l_Result;
	//creating objects/variables
	l_Result.SetID(glCreateShader(GL_GEOMETRY_SHADER));
	l_Result.SetFilePath(a_FilePath);
	//read shader
	std::ifstream ShaderFile(a_FilePath);
	l_Result.SetFile(std::string((std::istreambuf_iterator<char>(ShaderFile)), (std::istreambuf_iterator<char>())));
	ShaderFile.close();
	const char *shaderCode = l_Result.GetRawFile().c_str();
	//creating shader source
	glShaderSource(l_Result.GetID(), 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(l_Result.GetID()))
	{
		std::cout << "Vertex shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Vertex Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(l_Result.GetID(), GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(l_Result.GetID(), sizeof(char) * 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
	return l_Result;
}

template<>
TessellationShader Load<TessellationShader>(const std::string &a_FilePath)
{
	TessellationShader l_Result;
	//creating objects/variables
	l_Result.SetID(glCreateShader(GL_TESS_CONTROL_SHADER));
	l_Result.SetFilePath(a_FilePath);
	//read shader
	std::ifstream ShaderFile(a_FilePath);
	l_Result.SetFile(std::string((std::istreambuf_iterator<char>(ShaderFile)), (std::istreambuf_iterator<char>())));
	ShaderFile.close();
	const char *shaderCode = l_Result.GetRawFile().c_str();
	//creating shader source
	glShaderSource(l_Result.GetID(), 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(l_Result.GetID()))
	{
		std::cout << "Vertex shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Vertex Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(l_Result.GetID(), GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(l_Result.GetID(), sizeof(char) * 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
	return l_Result;
}

template<>
Font Load<Font>(const std::string &a_FilePath)
{
	FT_Error l_error;
	FT_Face l_Temp;
	l_error = FT_New_Face(FreeTypeWrap::m_Singleton.m_Library, a_FilePath.c_str(), 0, &l_Temp);
	if (l_error)
	{
		std::cout << "Error Loading Font" << std::endl;
		exit(-1);
	}
	Font f;
	f.m_Face = l_Temp;
	f.LoadFontMap();
	return f;
}