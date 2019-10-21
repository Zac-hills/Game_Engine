#ifndef __MESH_H__
#define __MESH_H__
#include "Component.h"

class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

	unsigned int mesh_ptr = NULL;
	unsigned int mesh_size = NULL;
	const char* meshFilePath;
};


#endif