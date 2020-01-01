#pragma once
#include <string>
#include "Entity.h"

class Component
{
public:
	Component(Entity &a_Object) : m_Object(a_Object) {}

	virtual ~Component() {};

	virtual std::string ToString() = 0;

	Entity& getEntity() { return m_Object; }
protected:
	Entity & m_Object;
};