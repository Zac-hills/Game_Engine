#include "ShaderManager.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

ShaderManager::ShaderManager()
{
	std::cout << "Shader Manager Created. \n";
}

ShaderManager::~ShaderManager()
{
	std::cout << "Shader Manager Destroyed. \n";
	//for (auto map : Program_Hash)
	//{
	//	glDeleteProgram(map.second.Program_ptr);
	//}
}

void ShaderManager::loadStandardShaders()
{
	//deferred vertex
	//deferred frag no texture only mesh
	static VertexShader vs;
	vs.ShaderFilePath = "./Assets/Shaders/Vertex/DeferredRendering.txt";
	static FragmentShader fs;
	fs.ShaderFilePath = "./Assets/Shaders/Fragment/DeferredRenderingMesh.txt";
	static Program MeshOnly;

	SHADER_MANAGER.loadShader(vs);
	SHADER_MANAGER.loadShader(fs);
	SHADER_MANAGER.createProgram(vs, fs, MeshOnly);
	SHADER_MANAGER.Program_Hash[MeshOnly.Flag] = MeshOnly;
	//Pass Through Vertex
	//Color Attachment fragment shader
	static VertexShader vs1;
	vs1.ShaderFilePath = "./Assets/Shaders/Vertex/PassThrough.txt";
	vs1.Flag |= FULL_SCREEN_UNIFORM;
	static FragmentShader fs1;
	fs1.ShaderFilePath = "./Assets/Shaders/Fragment/ColorAttachment.txt";
	fs1.Flag |= COLOR_ATTACHMENT_UNIFORM;
	static Program RenderColorAttachment;

	SHADER_MANAGER.loadShader(vs1);
	SHADER_MANAGER.loadShader(fs1);
	SHADER_MANAGER.createProgram(vs1, fs1, RenderColorAttachment);
	SHADER_MANAGER.Program_Hash[RenderColorAttachment.Flag] = RenderColorAttachment;

	//static VertexShader vs2;
	//vs2.ShaderFilePath = "./Assets/Shaders/Vertex/InterfaceQuadVert.txt";
	//static GeometryShader gs1;
	//gs1.ShaderFilePath = "./Assets/Shaders/Geometry/InterfaceQuads.txt";
	//gs1.Flag |= INTERFACE_UNIFORM;
	//static FragmentShader fs2;
	//fs2.ShaderFilePath = "./Assets/Shaders/Fragment/QuadInterfaceFragment.txt";
	//fs2.Flag |= TEXTURE_UNIFORM;
	//static Program InterfaceSquareProgram;

	//SHADER_MANAGER.loadShader(vs2);
	//SHADER_MANAGER.loadShader(gs1);
	//SHADER_MANAGER.loadShader(fs2);
	//SHADER_MANAGER.createProgram(vs2, gs1, fs2, InterfaceSquareProgram);
	//SHADER_MANAGER.Program_Hash[InterfaceSquareProgram.Flag] = InterfaceSquareProgram;
	unsigned int check = SHADER_MANAGER.Program_Hash.size();
}

void ShaderManager::bindProgram(unsigned int program)
{
	ActiveProgram = program;
	glUseProgram(program);
}

ShaderManager &ShaderManager::getShaderManager()
{
	static ShaderManager ONLY_ONE;
	return ONLY_ONE;
}

bool ShaderManager::compileShader(unsigned int shader_ptr)
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


void ShaderManager::loadShader(VertexShader &s)
{
	//creating objects/variables
	s.Shader_ptr = glCreateShader(GL_VERTEX_SHADER);
	
	//read shader
	std::ifstream ShaderFile(s.ShaderFilePath);
	std::string rawFile((std::istreambuf_iterator<char>(ShaderFile)), (std::istreambuf_iterator<char>()));
	ShaderFile.close();
	const char *shaderCode = rawFile.c_str();
	//creating shader source
	glShaderSource(s.Shader_ptr, 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(s.Shader_ptr))
	{
		std::cout << "Vertex shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Vertex Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(s.Shader_ptr, GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(s.Shader_ptr, sizeof(char)* 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;
		
	}
}

void ShaderManager::loadShader(FragmentShader &s)
{
	//creating objects/variables
	s.Shader_ptr = glCreateShader(GL_FRAGMENT_SHADER);

	//read shader
	std::ifstream ShaderFile(s.ShaderFilePath);
	std::string rawFile((std::istreambuf_iterator<char>(ShaderFile)), (std::istreambuf_iterator<char>()));
	ShaderFile.close();
	const char *shaderCode = rawFile.c_str();
	//creating shader source
	glShaderSource(s.Shader_ptr, 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(s.Shader_ptr))
	{
		std::cout << "Fragment shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Fragment Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(s.Shader_ptr, GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(s.Shader_ptr, sizeof(char)* 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
}

void ShaderManager::loadShader(GeometryShader &s)
{
	//creating objects/variables
	s.Shader_ptr = glCreateShader(GL_GEOMETRY_SHADER);

	//read shader
	std::ifstream ShaderFile(s.ShaderFilePath);
	std::string rawFile((std::istreambuf_iterator<char>(ShaderFile)), (std::istreambuf_iterator<char>()));
	ShaderFile.close();
	const char *shaderCode = rawFile.c_str();
	//creating shader source
	glShaderSource(s.Shader_ptr, 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(s.Shader_ptr))
	{
		std::cout << "Geometry shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Geometry Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(s.Shader_ptr, GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(s.Shader_ptr, sizeof(char)* 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
}

void ShaderManager::loadShader(TessalationShader &s)
{
	//creating objects/variables
	s.Shader_ptr = glCreateShader(GL_TESS_CONTROL_SHADER);

	//read shader
	std::ifstream ShaderFile(s.ShaderFilePath);
	std::string rawFile((std::istreambuf_iterator<char>(ShaderFile)), (std::istreambuf_iterator<char>()));
	ShaderFile.close();
	const char *shaderCode = rawFile.c_str();
	//creating shader source
	glShaderSource(s.Shader_ptr, 1, &shaderCode, NULL);

	//compiling shader
	if (compileShader(s.Shader_ptr))
	{
		std::cout << "Vertex shader compiled." << std::endl;
	}
	else
	{
		std::cout << "Vertex Shader did not Compile." << std::endl;
		std::vector<char> infoLog;
		infoLog.resize(512);

		GLint lengthLog;

		glGetShaderiv(s.Shader_ptr, GL_INFO_LOG_LENGTH, &lengthLog);
		glGetShaderInfoLog(s.Shader_ptr, sizeof(char)* 512, &lengthLog, &infoLog[0]);

		std::cout << std::string(infoLog.begin(), infoLog.end()) << std::endl;

	}
}

void ShaderManager::createProgram(Shader &s1, Shader &s2, Program &p)
{
	GLint shadertype;
	p.Program_ptr = glCreateProgram();
		glGetShaderiv(s1.Shader_ptr, GL_SHADER_TYPE, &shadertype);
		if (shadertype == GL_FRAGMENT_SHADER)
		{
			glAttachShader(p.Program_ptr, s1.Shader_ptr);
		}
		else if (shadertype == GL_VERTEX_SHADER)
		{
			glAttachShader(p.Program_ptr, s1.Shader_ptr);
		}
		else
		{
			std::cout << "The specified shader program will not run check shader configuration.\n";
		}
		GLint shadertype1;

		glGetShaderiv(s2.Shader_ptr, GL_SHADER_TYPE, &shadertype1);
		if (shadertype1 == GL_FRAGMENT_SHADER)
		{
			glAttachShader(p.Program_ptr, s2.Shader_ptr);
		}
		else if (shadertype1 == GL_VERTEX_SHADER)
		{
			glAttachShader(p.Program_ptr, s2.Shader_ptr);
		}
		else
		{
			std::cout << "The specified shader program will not run check shader configuration.\n";
		}
		glLinkProgram(p.Program_ptr);
		GLint linkStatus;
		glGetProgramiv(p.Program_ptr, GL_LINK_STATUS, &linkStatus);

		if (linkStatus)
		{
			std::cout << "linked the shaders. \n";
			p.Flag = s1.Flag | s2.Flag;
		}
		else
		{
			std::cout << "did not link the shaders.";
		}

}

void ShaderManager::createProgram(Shader &, Shader &, Shader &, Program &)
{

}

void ShaderManager::createProgram(Shader &, Shader &, Shader &, Shader &, Program &)
{

}

GLint ShaderManager::getUniformLocation(const char* uniform)
{
	GLint location = glGetUniformLocation(ActiveProgram, uniform);
	return location;
}
void ShaderManager::sendToShader(const char* uniformName, float f)
{
	GLint location = getUniformLocation(uniformName);

	glProgramUniform1f(ActiveProgram, location, f);
}
void ShaderManager::sendToShader(const char* uniformName, vec3 &v)
{
	GLint location = getUniformLocation(uniformName);
	glProgramUniform3f(ActiveProgram, location, v.x, v.y, v.z);
}
void ShaderManager::sendToShader(const char* uniformName, mat4 &m)
{
	GLint location = getUniformLocation(uniformName);
	glProgramUniformMatrix4fv(ActiveProgram, location, 1, false, m.data);

}
void ShaderManager::sendToShader(const char* uniformName, vec4 &v)
{
	GLint location = getUniformLocation(uniformName);
	glProgramUniform4f(ActiveProgram, location, v.x, v.y, v.y, v.w);
}
void ShaderManager::sendToShader(const char* uniformName, int i)
{
	GLint location = getUniformLocation(uniformName);
	glProgramUniform1i(ActiveProgram, location, i);
}

void ShaderManager::sendToShader(const char *uniformName, vec2 &v)
{
	GLint location = getUniformLocation(uniformName);
	glProgramUniform2f(ActiveProgram, location, v.x, v.y);
}