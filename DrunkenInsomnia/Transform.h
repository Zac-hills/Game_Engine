#pragma once
#include "Component.h"
#include "MatrixMath.h"
#include "Entity.h"
#include <functional>

class Transform : public Component 
{
public:
	Transform(Entity &a_Object, Transform& parent);
	Transform(Entity &object);
	std::string ToString();

	mat4 getLocal();
	mat4 getWorld();

	void setLocal(const mat4 &a_Mat);
	void setWorld(const mat4 &a_Mat);

	vec3 getPosition() const;
	void setPosition(const vec3 &vec);

	vec3 getForward() const;
	vec3 getUp() const;
	vec3 getRight() const;

	Transform &getParent();
	void setParent(Transform& parent);
	std::vector<std::reference_wrapper<Transform>> getChildren();

	bool operator==(Transform &other);

private:
	mat4 m_LocalOrientation;
	mat4 m_GlobalOrientation;
	std::mutex m_Mutex;
	Transform* parent;
	std::vector<std::reference_wrapper<Transform>> children;
	static Transform ROOT;
	static Entity rootEntity;
	void calculateChildren(const mat4 &parent);
	Transform(Entity &object, const mat4 &position);
	static void calculateGlobal();
};