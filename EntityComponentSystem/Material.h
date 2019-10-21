#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Component.h"

#define NULL_UNIFORM 0x0000
#define MESH_UNIFORM 0x0001
#define TEXTURE_UNIFORM 0x0002
#define NORMAL_MAP_UNIFORM 0x0004
#define INCANDESCENT_UNIFORM 0x0008
#define SPECULAR_UNIFORM 0x0010
#define DISPLACEMENT_UNIFORM 0x0020
#define ALPHA_UNIFORM 0x0040
#define INTERFACE_UNIFORM 0x0080
#define GEOMETRY_PRIMITIVE_CUBE 0x0160
#define GEOMETRY_PRIMITIVE_SPHERE 0X0320
#define GEOMETRY_PRIMITIVE_CAPSULE 0X0640

class Material : public Component
{
public:
	Material();
	~Material();

	unsigned short Flag = NULL_UNIFORM;

	unsigned int ProgramIndex;

	const char* NormalFilePath;
	int Normal_ptr;
	const char* DisplacementFilePath;
	int Displacement_ptr;
	const char* TextureFilePath;
	int Texture_ptr;
	const char* SpecularFilePath;
	int Specular_ptr;
	const char* IncandescentFilePath;
	int Incandescent_ptr;
};




#endif