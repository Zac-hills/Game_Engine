#include "Physics.h"
using namespace physics2D;



Collider::Collider(Entity &a_Object, Transform &a_Transform) : Component(a_Object), m_Transform(a_Transform) {}
vec3 Collider::GetPosition() const 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return  m_Transform.getLocal().position; 
}

void Collider::SetPosition(const vec2 & a_Position)
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Transform.setPosition(vec3(a_Position.x, a_Position.y, 0.0f));
}
std::string Collider::ToString() { return std::string("Collider "); }

QuadCollider::QuadCollider(Entity &a_Object, Transform &a_Transform, const unsigned int a_Width, const unsigned int a_Height) : Collider(a_Object, a_Transform),
m_Height(a_Height), m_Width(a_Width) {}  
unsigned int QuadCollider::GetHeight() const 
{
	return m_Height; 
}

void QuadCollider::SetHeight(const unsigned int a_Height)
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Height = a_Height;
}

unsigned int QuadCollider::GetWidth() const 
{
	return m_Width; 
}

void QuadCollider::SetWidth(const unsigned int a_Width)
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Width = a_Width;
}

std::string QuadCollider::ToString() 
{
	return std::string("");
};

//finish collision
bool QuadCollider::Colliding(const vec2 &a_Point, const QuadCollider &a_Quad)
{
	return true;
}


bool CircleCollider::Colliding(vec3 &a_Point, CircleCollider &a_Circle)
{
	vec3 l_Distance = a_Point - a_Circle.m_Transform.getLocal().position;
	float l_Magnitude = l_Distance.magnitude();
	return (l_Magnitude < a_Circle.m_Radius);
}

bool CircleCollider::Colliding(CircleCollider &a_Circle1, CircleCollider &a_Circle2) 
{
	return ((a_Circle1.m_Transform.getLocal().position - a_Circle2.m_Transform.getLocal().position).magnitude() < a_Circle1.m_Radius + a_Circle2.m_Radius);
}



CircleCollider::CircleCollider(Entity &a_Object, Transform &a_Transform, const unsigned int a_Radius) : Collider(a_Object, a_Transform)
,m_Radius(a_Radius) {}

std::string CircleCollider::ToString() 
{
	return std::string(""); 
}

void CircleCollider::SetRadius(const unsigned int a_Radius)
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Radius = a_Radius;
}

unsigned int CircleCollider::GetRadius() const 
{
	return m_Radius;
}