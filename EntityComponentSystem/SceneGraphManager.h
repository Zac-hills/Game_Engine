#ifndef __SCENE_GRAPH_H__
#define __SCENE_GRAPH_H__
#include <unordered_map>
#define SCENE_MANAGER SceneGraph::_sceneGraph()
#include "MatrixMath.h"
#include "Transform.h"

class SceneNode
{
public:
	SceneNode();
	SceneNode(Transform &a_t);
	~SceneNode();
	Transform *m_transform;
	SceneNode *m_parent;
	mat4 m_globalTransform;
	std::vector<std::string> children;
};



class SceneGraph 
{
public:
	static SceneGraph &_sceneGraph();
	void addSceneNode(SceneNode sc, std::string EntityName);
	void updateSceneNode(std::string currentName, std::string newName);
	void removeSceneNode(std::string EntityName);
	void changeParent(std::string EntityName, std::string parent);
	SceneNode &getScenePos(std::string entity);
	Transform &getParent(std::string entityName);
	void update();
	void calcGlobalMatrix(mat4 &m, SceneNode &s);
	std::unordered_map<std::string, SceneNode> sceneMap;
private:

	SceneGraph();
	~SceneGraph();
};

#endif