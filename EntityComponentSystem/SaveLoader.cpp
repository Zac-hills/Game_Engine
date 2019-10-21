#include "SaveLoader.h"
#include <iostream>
#include <fstream>
#include "Transform.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "ComponentManager.h"
#include "SceneGraphManager.h"

SaveLoader::SaveLoader(){}

SaveLoader::~SaveLoader(){}


SaveLoader &SaveLoader::getSaveLoader()
{
	static SaveLoader ONLY_ONE;
	return ONLY_ONE;
}

void writeTransform(std::ofstream _w, Transform *t)
{
	_w << "Transform <" << t->m_position.toString().c_str() << ">" << std::endl;
}

void writeCamera(std::ofstream _w, Camera *C)
{
	_w << "Camera <" << C->perspectiveMatrix.toString().c_str() << ">" << std::endl;
}

void writeMaterial(std::ofstream _w, Material *m)
{
	_w << "Material <" << std::endl;
	if (m->Normal_ptr != -1)
	{
		_w << "Normal <" << m->NormalFilePath << ">" << std::endl;
	}
	if (m->Displacement_ptr != -1)
	{
		_w << "Displacement <" << m->DisplacementFilePath << ">" << std::endl;
	}
	if (m->Texture_ptr != -1)
	{
		_w << "Texture <" << m->TextureFilePath << ">" << std::endl;
	}
	if (m->Specular_ptr != -1)
	{
		_w << "Specular <" << m->SpecularFilePath << ">" << std::endl;
	}
	if (m->Incandescent_ptr != -1)
	{
		_w << "Incandescent <" << m->IncandescentFilePath << ">" << std::endl;
	}
	_w << "End>" << std::endl;
}

void writeMaterial(std::ofstream _w, Mesh *m)
{
	if (m->mesh_ptr != 0)
	{
		_w << "Mesh <" << m->meshFilePath << ">" << std::endl;
	}
}

void writeEntity(std::ofstream _w, std::string e)
{
	_w << "Entity <" << e.c_str() << ">" << std::endl;
}

void writeSceneNode(std::ofstream _w, SceneNode *s, std::string entityName, std::string parent)
{
	_w << "SceneNode <" << std::endl;
	_w << "EntityName <" << entityName.c_str() << ">" << std::endl;
	_w << "GlobalTransform <" << s->m_globalTransform.toString().c_str() << ">" << std::endl;
	for (unsigned int i = 0; i < s->children.size(); i++)
	{
		_w << "Child <" << s->children[i].c_str() << ">" << std::endl;
	}
	_w << "Parent <" << parent.c_str() << ">" << std::endl;
	_w << "End>" << std::endl;
}

void SaveLoader::Save(const char* FileName)
{
	std::ofstream Writer;
	Writer.open(FileName);

}

void SaveLoader::Load(const char *filePath)
{
	
}