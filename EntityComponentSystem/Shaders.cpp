#include "Shaders.h"

Shader::Shader()
{
	memset(&Flag, 0, 16);
}

Shader::~Shader(){}

VertexShader::VertexShader()
{
	memset(&Flag, 0, 16);
}

VertexShader::~VertexShader()
{
	glDeleteShader(Shader_ptr);
}

FragmentShader::FragmentShader()
{
	memset(&Flag, 0, 16);
}

FragmentShader::~FragmentShader()
{
	glDeleteShader(Shader_ptr);
}

GeometryShader::GeometryShader()
{
	memset(&Flag, 0, 16);
}

GeometryShader::~GeometryShader()
{
	glDeleteShader(Shader_ptr);
}

TessalationShader::TessalationShader()
{
	memset(&Flag, 0, 16);
}

TessalationShader::~TessalationShader()
{
	glDeleteShader(Shader_ptr);
}
