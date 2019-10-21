#include "Transform.h"

Transform::Transform(){}

Transform::~Transform(){}

vec3 &Transform::up()
{
	return m_position.up;
}

const vec3 &Transform::forward() const
{
	return m_position.forward;
}

void Transform::Setforward(vec3 &v) 
{
	
}

vec3 &Transform::right()
{
	return m_position.right;
}

vec3 &Transform::position()
{
	return m_position.position;
}

unsigned int Transform::childCount() const
{
	return m_numChild;
}

//mat4 & Transform::getMatrix()
//{
//	return m_position;
//}
