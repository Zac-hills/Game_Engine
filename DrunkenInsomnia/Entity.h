#pragma once
#include "UniqueIdentifier.h"


class Entity 
{
public:
	Entity() : m_ID(m_UniqueIDS.GetID()){}
	virtual ~Entity() { m_UniqueIDS.ReleaseID(m_ID); };
	virtual void OnClick() {}
	static UniqueIdentifier m_UniqueIDS;
	unsigned int m_ID;
	bool operator==(const Entity & other) const;
};
