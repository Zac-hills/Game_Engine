#include "Entity.h"

UniqueIdentifier Entity::m_UniqueIDS;

bool Entity::operator==(const Entity & other) const
{
	return (m_ID == other.m_ID);
}
