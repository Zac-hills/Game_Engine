#include "SceneManager.h"

Entity e;
Transform RootTransform(e);

SceneNode SceneNode::ROOT(RootTransform, true);

SceneNode::SceneNode(Transform & a_Transform, const bool isRoot) : m_Transform(a_Transform)
{
	if (isRoot)
	{
		m_Parent = nullptr;
		m_Depth = 0;
	}
}

SceneNode::SceneNode(Transform &a_Transform) : m_Transform(a_Transform)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Parent = &ROOT;
	ROOT.m_Children.push_back(this);
	m_Depth = m_Parent->m_Depth + 1;
}

SceneNode::SceneNode(Transform &a_Transform, SceneNode &a_Parent) : m_Transform(a_Transform)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Parent = &a_Parent;
	a_Parent.m_Children.push_back(this);
	m_Depth = m_Parent->m_Depth + 1;
}

SceneNode::~SceneNode() 
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (auto &it : m_Children)
	{
		it->SetParent(ROOT);
	}
	if (m_Parent != nullptr) {
		m_Parent->m_Children.remove(this);
		m_Parent = nullptr;
	}
}

void SceneNode::SetParent(SceneNode &a_Parent)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_Parent->m_Children.remove(this);
	m_Parent = &a_Parent;
	a_Parent.m_Children.push_back(this);
	m_Depth = m_Parent->m_Depth + 1;
	for (auto &it : m_Children)
	{
		UpdateDepth(*it);
	}
}

void SceneNode::UpdateDepth(SceneNode &a_SceneNode)
{
	a_SceneNode.m_Depth = m_Parent->m_Depth + 1;
	for (auto &it : m_Children)
	{
		UpdateDepth(*it);
	}
}

SceneNode &SceneNode::GetParent() 
{
	return *m_Parent;
}


unsigned int SceneNode::GetNumOfChildren() const
{
	return m_Children.size();
}

Transform& SceneNode::GetTransform()
{
	return m_Transform;
}

void SceneManager::CalculateGlobalTransforms() 
{
	TreeTraversal(SceneNode::ROOT, SceneNode::ROOT.m_Transform.getLocal());
}

void SceneManager::TreeTraversal(SceneNode &a_SceneNode, mat4 &a_WorldMat)
{
	a_SceneNode.GetTransform().setWorld(a_SceneNode.GetParent().GetTransform().getWorld() * a_SceneNode.GetTransform().getLocal());

	for (auto &it : a_SceneNode.m_Children)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		TreeTraversal(*it, a_SceneNode.GetTransform().getWorld());
	}
}