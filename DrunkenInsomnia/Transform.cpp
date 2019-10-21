#include "Transform.h"

Transform::Transform(Entity &a_Object) : Component(a_Object) {}

std::string Transform::ToString() { return std::string(""); }

mat4 Transform::GetLocal()
{
	return m_LocalOrientation; 
}

mat4 Transform::GetWorld() 
{
	return m_GlobalOrientation;
}

void Transform::SetLocal(const mat4 &a_Mat)
{
	std::lock_guard<std::mutex>lock(m_Mutex);
	m_LocalOrientation = a_Mat;
}

void Transform::SetWorld(const mat4 &a_Mat)
{
	std::lock_guard<std::mutex>lock(m_Mutex);
	m_GlobalOrientation = a_Mat;
}

vec3 Transform::GetPosition() const
{
	return m_LocalOrientation.position;
}

void Transform::SetPosition(const vec3 &vec)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_LocalOrientation.position = vec;
}