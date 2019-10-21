#pragma once
#include "VectorMath.h"
#include "Component.h"

class Quad : public Component
{
public:
	//position is at the center, width and height in pixels
	Quad(Entity &a_Object, vec3 &a_Pos, const unsigned int a_Width, const unsigned int a_Height) : Component(a_Object), m_Position(a_Pos), m_Height(a_Height), m_Width(a_Width) {}
	unsigned int GetHeight() const { return m_Height; }
	void SetHeight(const unsigned int a_Height) 
	{
		std::lock_guard<std::mutex> Lock(m_Mutex);
		m_Height = a_Height;
	}
	unsigned int GetWidth() const
	{
		return m_Width;
	}
	void SetWidth(const unsigned int a_Width) 
	{
		std::lock_guard<std::mutex> Lock(m_Mutex);
		m_Width = a_Width;
	}
	std::string ToString() { return std::string(""); }
	void SetColor(const vec3 &Color) 
	{
		std::lock_guard<std::mutex> Lock(m_Mutex);
		m_RGB = Color;
	}
	vec3 GetColor() const 
	{
		return m_RGB; 
	}
private:
	unsigned int m_Height = 0;
	unsigned int m_Width = 0;
	vec3 &m_Position;
	vec3 m_RGB;
	std::mutex m_Mutex;
};

class Light : public Component 
{
public:
	Light(Entity &a_Object, vec3 &a_Pos, const float a_Radius, const float a_Attenuation) : Component(a_Object), m_Radius(a_Radius), m_Attenuation(a_Attenuation){}

private:
	float m_Attenuation = 0;
	float m_Radius = 0;
};

class Sprite : public Component 
{
public:
	Sprite(Entity &object, const vec2 size = vec2(1,1)) : Component(object), size(size)
	{
		
	}

private:
	vec2 size;
};