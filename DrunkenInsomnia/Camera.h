#pragma once
#include "Entity.h"
#include "MatrixMath.h"
#include "Transform.h"

class Camera : public Component
{
public:
	Camera(Entity &a_Entity, Transform &a_Transform) : Component(a_Entity), m_Transform(a_Transform){}
	~Camera() {}

	mat4 GetProjectionMatrix() const;
	mat4 GetViewMatrix() const;

	void SetProjection(const float a_right, const float a_left, const float a_top, const float a_bottom, const float a_near, const float a_far);

	void Follow(const Entity &a_e, const vec3 &a_Distance=vec3(0.0f,0.0f,10.0f));


private:
	mat4 m_Projection;
	Transform &m_Transform;
};
