#include "Wrapper.h"
#include "Entity.h"
#include "Transform.h"
#include "ComponentManager.h"
#include "SceneGraphManager.h"
#include "Material.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "ImageLoader.h"
#include "BufferManager.h"
#include "RenderManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include "InterfaceSquareLayer.h"

extern  SceneNode Scene;
extern Transform root;


bool createNewEntity(char *c)
{
	if (CMP_MANAGER.nameAvailable(c))
	{
		Entity *e = new Entity(c);
		Transform *t = new Transform();
		CMP_MANAGER.addComponent<Entity>(c, e);
		CMP_MANAGER.addComponent<Transform>(c, t);
		SceneNode sc(*t);
		SCENE_MANAGER.addSceneNode(sc, e->entityName);
		return true;
	}
	return false;
}

void createNewInterface(char *name)
{
	if (CMP_MANAGER.nameAvailable(name))
	{
		Entity *e = new Entity(name);

	}
}

void deleteEntity(char *name)
{
	CMP_MANAGER.deleteComponents(name);
	SCENE_MANAGER.removeSceneNode(name);
	BUFFER_MANAGER.removeReference(name);
	if (CMP_MANAGER.renderEntities.find(name) != CMP_MANAGER.renderEntities.end())
	{
		CMP_MANAGER.renderEntities.erase(name);
	}
	else if (CMP_MANAGER.renderAlphaEntities.find(name) != CMP_MANAGER.renderAlphaEntities.end())
	{
		CMP_MANAGER.renderAlphaEntities.erase(name);
	}
}

bool changeEntityName(char *currentName, char *newName)
{
	if (CMP_MANAGER.nameAvailable(newName))
	{
		CMP_MANAGER.changeName(currentName, newName);

		SCENE_MANAGER.updateSceneNode(currentName, newName);
		if (CMP_MANAGER.renderEntities.find(currentName) != CMP_MANAGER.renderEntities.end())
		{
			CMP_MANAGER.renderEntities.erase(currentName);
			CMP_MANAGER.renderEntities[newName] = newName;
		}
		else if (CMP_MANAGER.renderAlphaEntities.find(currentName) != CMP_MANAGER.renderAlphaEntities.end())
		{
			CMP_MANAGER.renderAlphaEntities.erase(currentName);
			CMP_MANAGER.renderAlphaEntities[newName] = newName;
		}
		return true;
	}

	return false;
}

void parentEntity(char *entityName, char *parent)
{
	SCENE_MANAGER.changeParent(entityName, parent);
}

void addMaterial(char *entityName)
{
	Material *m = new Material();
	CMP_MANAGER.addComponent(entityName, m);
	CMP_MANAGER.renderEntities[entityName] = entityName;
}

void removeMaterial(char *entityName)
{
	CMP_MANAGER.deleteComponent<Material>(entityName);
	if (CMP_MANAGER.renderEntities.find(entityName) != CMP_MANAGER.renderEntities.end())
	{
		CMP_MANAGER.renderEntities.erase(entityName);
	}
	else
	{
		CMP_MANAGER.renderAlphaEntities.erase(entityName);
	}
}

void isAlpha(char *entityName)
{
	CMP_MANAGER.getComponent<Material>(entityName)->Flag |= ALPHA_UNIFORM;
	CMP_MANAGER.renderEntities.erase(entityName);
	CMP_MANAGER.renderAlphaEntities[entityName] = entityName;
}

void changeMaterialNormalPath(char *entityName, char *filePath)
{
	CMP_MANAGER.getComponent<Material>(entityName)->NormalFilePath = filePath;
	CMP_MANAGER.getComponent<Material>(entityName)->Normal_ptr = IMAGE_LOADER.loadImage(filePath);
	CMP_MANAGER.getComponent<Material>(entityName)->Flag |= NORMAL_MAP_UNIFORM;
}

void changeMaterialTexturePath(char *entityName, char *filePath)
{
	CMP_MANAGER.getComponent<Material>(entityName)->TextureFilePath = filePath;
	CMP_MANAGER.getComponent<Material>(entityName)->Texture_ptr = IMAGE_LOADER.loadImage(filePath);
	CMP_MANAGER.getComponent<Material>(entityName)->Flag |= TEXTURE_UNIFORM;
}

void changeMaterialDisplacementPath(char *entityName, char *filePath)
{
	CMP_MANAGER.getComponent<Material>(entityName)->DisplacementFilePath = filePath;
	CMP_MANAGER.getComponent<Material>(entityName)->Displacement_ptr = IMAGE_LOADER.loadImage(filePath);
	CMP_MANAGER.getComponent<Material>(entityName)->Flag |= DISPLACEMENT_UNIFORM;
}

void changeMaterialSpecularPath(char *entityName, char *filePath)
{
	CMP_MANAGER.getComponent<Material>(entityName)->SpecularFilePath = filePath;
	CMP_MANAGER.getComponent<Material>(entityName)->Specular_ptr = IMAGE_LOADER.loadImage(filePath);
	CMP_MANAGER.getComponent<Material>(entityName)->Flag |=  SPECULAR_UNIFORM;
}

void changeMaterialIncandescentPath(char *entityName, char *filePath)
{
	CMP_MANAGER.getComponent<Material>(entityName)->IncandescentFilePath = filePath;
	CMP_MANAGER.getComponent<Material>(entityName)->Incandescent_ptr = IMAGE_LOADER.loadImage(filePath);
	CMP_MANAGER.getComponent<Material>(entityName)->Flag |= INCANDESCENT_UNIFORM;
}

void addMesh(char *entityName)
{
	Mesh *m = new Mesh();
	CMP_MANAGER.addComponent(entityName, m);
}

void addSquareInterface(char *entityName)
{
	InterfaceSquareLayer *IsL = new InterfaceSquareLayer();
	CMP_MANAGER.addComponent(entityName, IsL);
}

void deleteMesh(char *entityName)
{
	CMP_MANAGER.deleteComponent<Mesh>(entityName);
}

void changeMeshPath(char *entityName, char *path)
{
	CMP_MANAGER.getComponent<Mesh>(entityName)->meshFilePath = path;
	MESH_LOADER.loadMesh(path, *CMP_MANAGER.getComponent<Mesh>(entityName));
}

void addCamera(char *EntityName)
{
	Camera *c = new Camera();
	CMP_MANAGER.addComponent(EntityName, c);
}

void setCurrentCamera(char *entityName)
{
	RENDER_MANAGER.setCurrentCamera(entityName);
}


