#pragma once
#include <vector>
#include <list>
#include "Transform.h"
#include <unordered_map>

class SceneManager;

class SceneNode 
{
public:
	friend SceneManager;
	SceneNode(Transform &a_Transform);
	SceneNode(Transform &a_Transform, SceneNode &a_Parent);
	~SceneNode();
	void SetParent(SceneNode &a_Parent);
	SceneNode &GetParent();
	unsigned int GetNumOfChildren() const;

	Transform &GetTransform();				
	static SceneNode ROOT;

private:
	SceneNode(Transform &a_Transform, const bool isROOT);
	void UpdateDepth(SceneNode &a_SceneNode);
	std::list<SceneNode *> m_Children;
	SceneNode *m_Parent;
	Transform &m_Transform;
	unsigned int m_Depth = 0;
	std::mutex m_Mutex;
};

class SceneManager 
{
public:
	void CalculateGlobalTransforms();
private:
	//entity ID = key, mat4 is global transform
	std::unordered_map<unsigned int, mat4> GlobalTransformCache;
	void TreeTraversal(SceneNode &a_SceneNode, mat4 &a_WorldMat);
	std::mutex m_Mutex;
};