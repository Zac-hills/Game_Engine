#include "Entity.h"
#include "BufferManager.h"

unsigned int Entity::totalCount = 2000;

Entity::Entity(const std::string &s) : entityName(s)
{
	unique_id = totalCount;
	totalCount++;
	rgb.x = ((unique_id & 0x000000FF) >> 0) / 255.0f;
	rgb.y = ((unique_id & 0x0000FF00) >> 8) / 255.0f;
	rgb.z = ((unique_id & 0x00FF0000) >> 16) / 255.0f;
	BUFFER_MANAGER.EntityIDs[unique_id] = entityName;
}

Entity::~Entity(){}