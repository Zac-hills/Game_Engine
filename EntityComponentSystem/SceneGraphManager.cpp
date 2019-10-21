#include "SceneGraphManager.h"
#include "ComponentManager.h"

static Transform root;

static SceneNode Scene(root);

SceneNode::SceneNode() : m_transform(&root), m_parent(&Scene)
{
}

SceneNode::SceneNode(Transform &a_t) : m_transform(&a_t), m_parent(&Scene)
{
}

SceneNode::~SceneNode()
{
	m_parent = nullptr;
	children.clear();
}

SceneGraph::SceneGraph()
{
	std::cout << "Scene Graph Manager Created. \n";
}

SceneGraph::~SceneGraph()
{
	std::cout << "Scene Graph Manager Destroyed. \n";
}


SceneGraph &SceneGraph::_sceneGraph()
{
	static SceneGraph ONLY_ONE;
	return ONLY_ONE;
}

void SceneGraph::addSceneNode(SceneNode sc, std::string EntityName)
{
	sceneMap[EntityName] =  sc;
	Scene.children.push_back(EntityName);
}

void SceneGraph::removeSceneNode(std::string EntityName)
{
	if (sceneMap.find(EntityName) != sceneMap.end())
	{
		sceneMap.erase(EntityName);
	}
}

SceneNode &SceneGraph::getScenePos(std::string entityName)
{
	return sceneMap[entityName];
}

Transform &SceneGraph::getParent(std::string entityName)
{
	return *sceneMap[entityName].m_parent->m_transform;
}

void SceneGraph::updateSceneNode(std::string currentName, std::string newName)
{
	if (sceneMap.find(currentName) != sceneMap.end())
	{
		sceneMap[newName] = sceneMap[currentName];
		sceneMap.erase(currentName);
	}
}

void SceneGraph::changeParent(std::string entityName, std::string parent)
{
	if (sceneMap.find(entityName) != sceneMap.end() && sceneMap.find(parent) != sceneMap.end())
	{
			for (unsigned int i = 0; i < sceneMap[entityName].m_parent->children.size(); i++)
			{
				if (sceneMap[entityName].m_parent->children[i] == entityName)
				{
					sceneMap[entityName].m_parent->children.erase(sceneMap[entityName].m_parent->children.begin() + i);
				}
		}
		sceneMap[entityName].m_parent = &sceneMap[parent];
		sceneMap[entityName].m_transform->m_position = sceneMap[entityName].m_globalTransform * sceneMap[parent].m_globalTransform.inverse();
		sceneMap[parent].children.push_back(entityName);
	}
}
void SceneGraph::calcGlobalMatrix(mat4 &m, SceneNode &s)
{
	for (unsigned int i = 0; i < s.children.size(); i++)
	{
		sceneMap[s.children[i]].m_globalTransform = m * sceneMap[s.children[i]].m_transform->m_position;
		for (unsigned int k = 0; k < sceneMap[s.children[i]].children.size(); k++)
		{
			calcGlobalMatrix(sceneMap[s.children[i]].m_globalTransform, sceneMap[s.children[i]]);
		}
	}
}

void SceneGraph::update()
{
	mat4 cmt = Scene.m_transform->m_position;
	calcGlobalMatrix(cmt, Scene);
}