#ifndef __SHADER_H__
#define __SHADER_H__
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include "glew.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#define NULL_UNIFORM 0x0000
#define MESH_UNIFORM 0x0001
#define TEXTURE_UNIFORM 0x0002
#define NORMAL_MAP_UNIFORM 0x0004
#define INCANDESCENT_UNIFORM 0x0008
#define SPECULAR_UNIFORM 0x0010
#define FULL_SCREEN_UNIFORM 0x0020
#define COLOR_ATTACHMENT_UNIFORM 0x0040
#define INTERFACE_UNIFORM 0X0080

class Shader
{
public:
	Shader();
	~Shader();
	std::string ShaderFilePath;
	unsigned int Shader_ptr;
	unsigned short Flag;
};

class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader();
};

class FragmentShader : public Shader
{
public:
	FragmentShader();
	~FragmentShader();
};

class GeometryShader : public Shader
{
public:
	GeometryShader();
	~GeometryShader();
};

class TessalationShader : public Shader
{
public:
	TessalationShader();
	~TessalationShader();
};


#endif