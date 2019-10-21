#include "GL\glew.h"
#include "ShaderManager.h"
#include <iostream>
#include <vector>

// GL_FLOAT_VEC2_ARB 0x8B50
// GL_FLOAT_VEC3_ARB 0x8B51
// GL_FLOAT_VEC4_ARB 0x8B52
// GL_INT_VEC2_ARB 0x8B53
// GL_INT_VEC3_ARB 0x8B54
// GL_INT_VEC4_ARB 0x8B55
// GL_BOOL_ARB 0x8B56
// GL_BOOL_VEC2_ARB 0x8B57
// GL_BOOL_VEC3_ARB 0x8B58
// GL_BOOL_VEC4_ARB 0x8B59
// GL_FLOAT_MAT2_ARB 0x8B5A
// GL_FLOAT_MAT3_ARB 0x8B5B
// GL_FLOAT_MAT4_ARB 0x8B5C
// GL_SAMPLER_1D_ARB 0x8B5D
// GL_SAMPLER_2D_ARB 0x8B5E
// GL_SAMPLER_3D_ARB 0x8B5F
void ShaderManager::GetProgramInfo(Program &a_p)
{
	GLint numUniforms = 0;
	glGetProgramInterfaceiv(a_p.GetProgram(), GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
	const GLenum properties[4] = { GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION };

	for (int unif = 0; unif < numUniforms; ++unif)
	{
		GLint values[4];
		glGetProgramResourceiv(a_p.GetProgram(), GL_UNIFORM, unif, 4, properties, 4, NULL, values);

		// Skip any uniforms that are in a block.
		if (values[0] != -1)
			continue;

		// Get the name. Must use a std::vector rather than a std::string for C++03 standards issues.
		// C++11 would let you use a std::string directly.
		std::vector<GLchar> nameData;
		nameData.resize(values[2]);
		glGetProgramResourceName(a_p.GetProgram(), GL_UNIFORM, unif, nameData.size(), NULL, &nameData[0]);
		std::string name(nameData.begin(), nameData.end() - 1);
	}
}

void ShaderManager::CreateProgram(Program & a_Program)
{
	a_Program.SetProgram(glCreateProgram());
	for (auto it : a_Program.GetMap())
	{
		glAttachShader(a_Program.GetProgram(), it.second.GetID());
	}

	glLinkProgram(a_Program.GetProgram());
	GLint linkStatus;
	glGetProgramiv(a_Program.GetProgram(), GL_LINK_STATUS, &linkStatus);

	if (linkStatus)
	{
		std::cout << "linked the shaders. \n";
	}
	else
	{
		GLint length=0;
		GLsizei logLength=0;
		glGetProgramiv(a_Program.GetProgram(), GL_INFO_LOG_LENGTH, &length);
		GLchar *Log = new GLchar[length];
		glGetProgramInfoLog(a_Program.GetProgram(), length, &logLength, Log);
		std::cout << "did not link the shaders. " << std::endl << Log;
		delete[] Log;
	}
	GetProgramInfo(a_Program);
}

std::unordered_map<std::type_index, Shader>& Program::GetMap()
{
	return m_ShaderMap;
}
