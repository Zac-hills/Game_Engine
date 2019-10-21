#pragma once
#include "Component.h"
#include "MatrixMath.h"
#include "Entity.h"

class Transform : public Component 
{
public:
	Transform(Entity &a_Object);
	std::string ToString();

	mat4 GetLocal();
	mat4 GetWorld();

	void SetLocal(const mat4 &a_Mat);
	void SetWorld(const mat4 &a_Mat);

	vec3 GetPosition() const;
	void SetPosition(const vec3 &vec);

private:
	mat4 m_LocalOrientation;
	mat4 m_GlobalOrientation;
	std::mutex m_Mutex;
};