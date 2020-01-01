#include "Transform.h"

Entity Transform::rootEntity;
Transform Transform::ROOT(Transform::rootEntity, mat4());

Transform::Transform(Entity &a_Object, Transform& parent) : Component(a_Object), parent(&parent) {}

Transform::Transform(Entity &a_Object) : Component(a_Object), parent(&Transform::ROOT)
{
	Transform::ROOT.children.push_back(*this);
}

Transform::Transform(Entity &a_Object, const mat4& position) : Component(a_Object), parent(nullptr)
{
	m_LocalOrientation = position;
}

std::string Transform::ToString() { return std::string(""); }

mat4 Transform::getLocal()
{
	return m_LocalOrientation; 
}

mat4 Transform::getWorld() 
{
	return m_GlobalOrientation;
}

void Transform::setLocal(const mat4 &a_Mat)
{
	std::lock_guard<std::mutex>lock(m_Mutex);
	m_LocalOrientation = a_Mat;
}

void Transform::setWorld(const mat4 &a_Mat)
{
	std::lock_guard<std::mutex>lock(m_Mutex); 
	m_GlobalOrientation = a_Mat;
}

vec3 Transform::getPosition() const
{
	return m_LocalOrientation.position;
}

void Transform::setPosition(const vec3 &vec)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_LocalOrientation.position = vec;
}

vec3 Transform::getForward() const 
{
	return m_GlobalOrientation.forward;
}

vec3 Transform::getUp() const
{
	return m_GlobalOrientation.up;
}

vec3 Transform::getRight() const
{
	return m_GlobalOrientation.right;
}

Transform& Transform::getParent() 
{
	return *parent;
}

void Transform::setParent(Transform& parent)
{
	for (unsigned int i=0; i < this->parent->children.size(); ++i)
	{
		if (this->parent->children[i].get() == *this)
		{
			this->parent->children.erase(this->parent->children.begin() + i);
		}
	}

	this->parent = &parent;
	this->parent->children.push_back(*this);
}

std::vector<std::reference_wrapper<Transform>> Transform::getChildren()
{
	return children;
}

bool Transform::operator==(Transform & other) 
{
	return this->getEntity().m_ID == other.getEntity().m_ID;
}

void Transform::calculateGlobal()
{
	ROOT.calculateChildren(ROOT.getWorld());
}

void Transform::calculateChildren(const mat4& parent)
{
	setWorld(getLocal() * parent);
	for (auto &child : children)
	{
		child.get().calculateChildren(getWorld());
	}
}
