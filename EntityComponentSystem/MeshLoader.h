#ifndef __MESHLOADER_H__
#define __MESHLOADER_H__
#define MESH_LOADER MeshLoader::getMeshLoader()
#include <string> 
#include "Mesh.h"

class MeshLoader
{
private:
	MeshLoader();
	~MeshLoader();

public:
	void readBinaryMesh(std::string &, Mesh &m);
	void loadMesh(std::string, Mesh &m);
	static MeshLoader &getMeshLoader();
};


#endif
