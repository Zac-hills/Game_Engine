#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <iostream>
#define NAME(x) #x
#include "Component.h"
#include "VectorMath.h"

class Entity : public Component
{
public:
	Entity(const std::string &s);
	~Entity();
	std::string entityName;
	unsigned int unique_id;
	static unsigned int totalCount;
	vec3 rgb;
};



#endif