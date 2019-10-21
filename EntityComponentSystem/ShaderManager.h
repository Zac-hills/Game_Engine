#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__
#include "Shaders.h"
#define SHADER_MANAGER ShaderManager::getShaderManager()
#include <unordered_map>
#include "Program.h"
#include "MatrixMath.h"

class ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();

public:

	static ShaderManager &getShaderManager();
	void loadStandardShaders();

	bool compileShader(unsigned int);
	void loadShader(VertexShader &);
	void loadShader(FragmentShader &);
	void loadShader(GeometryShader &);
	void loadShader(TessalationShader &);

	void createProgram(Shader &, Shader &, Program &);
	void createProgram(Shader &, Shader &, Shader &, Program &);
	void createProgram(Shader &, Shader &, Shader &, Shader &, Program &);

	void bindProgram(unsigned int program);
	GLint getUniformLocation(const char *uniform);
	void sendToShader(const char *uniformName, float f);
	void sendToShader(const char *uniformName, vec3 &v);
	void sendToShader(const char *uniformName, vec4 &v);
	void sendToShader(const char *uniformName, mat4 &m);
	void sendToShader(const char *uniformName, int i);
	void sendToShader(const char *uniformName, vec2 &v);

	unsigned int ActiveProgram;

	std::unordered_map<std::string, Shader> Shader_Hash;
	std::unordered_map<unsigned short, Program> Program_Hash;
};



#endif