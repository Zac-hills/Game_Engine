#ifndef __WRAPPER_H__
#define __WRAPPER_H__
#include "LibSettings.h"

#ifdef __cplusplus
extern "C"
{
#endif

	bool LIB_API createNewEntity(char *name);
	void LIB_API deleteEntity(char *name);
	bool LIB_API changeEntityName(char *currentName, char *newName);
	void LIB_API parentEntity(char *EntityName, char *parent);
	void LIB_API addMaterial(char *entityName);
	void LIB_API removeMaterial(char *entityName);
	void LIB_API changeMaterialNormalPath(char *entityName,  char *filePath);
	void LIB_API changeMaterialTexturePath(char *entityName,  char *filePath);
	void LIB_API changeMaterialDisplacementPath(char *entityName,  char *filePath);
	void LIB_API changeMaterialSpecularPath(char *entityName,  char *filePath);
	void LIB_API changeIncandescentFilePath(char *entityName, char *filePath);
	void LIB_API isAlpha( char *entityName);
	void LIB_API addMesh( char *EntityName);
	void LIB_API deleteMesh( char *entityName);
	void LIB_API changeMeshPath( char *EntityName,  char *path);
	void LIB_API addCamera( char *EntityName);
	void LIB_API setCurrentCamera( char *entityName);
	void LIB_API createNewInterface(char *name);
	void LIB_API addSquareInterface(char *entityname);

#ifdef __cplusplus
}
#endif

#endif
























































































