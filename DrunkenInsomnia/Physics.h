#pragma once
#include "VectorMath.h"
#include "Component.h"
#include "Quaternions.h"
#include "Transform.h"

namespace physics2D
{
	class Collider : public Component
	{
	public:
		Collider(Entity &a_Object, Transform &a_Transform);
		vec3 GetPosition() const;
		void SetPosition(const vec2 &a_Position);
		std::string ToString();
	protected:
		Transform &m_Transform;
		mutable std::mutex m_Mutex;
	};

	class QuadCollider : public Collider 
	{
	public:
		QuadCollider(Entity &a_Object, Transform &a_Transform, const unsigned int a_Width, const unsigned int a_Height);
		unsigned int GetHeight() const;
		void SetHeight(const unsigned int a_Height);
		unsigned int GetWidth() const;
		void SetWidth(const unsigned int a_Width);
		std::string ToString();
		static bool Colliding(const vec2 &a_Point, const QuadCollider &a_Quad);
	private:
		unsigned int m_Height = 0;
		unsigned int m_Width = 0;
		std::mutex m_Mutex;
	};

	class CircleCollider : public Collider 
	{
	public:
		CircleCollider(Entity &a_Object, Transform &a_Transform, const unsigned int a_Radius);
		static bool Colliding(vec3 &a_Point, CircleCollider &a_Circle);
		static bool Colliding(CircleCollider &a_Circle1, CircleCollider &a_Circle2);
		std::string ToString();
		void SetRadius(const unsigned int a_Radius);
		unsigned int GetRadius() const;
	private:
		unsigned int m_Radius = 0;
		std::mutex m_Mutex;
	};

	class LineCollider : public Collider 
	{
	public:
		LineCollider(Entity &a_Object, Transform &a_Transform, vec3 &a_EndOfLine) : Collider(a_Object, a_Transform), m_EndOfLine(a_EndOfLine) {}
		std::string ToString() { return std::string(""); };
	private:
		vec3 &m_EndOfLine;
		std::mutex m_Mutex;
	};
}
