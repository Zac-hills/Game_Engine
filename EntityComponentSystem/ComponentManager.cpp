#include "ComponentManager.h"


ComponentManager::ComponentManager()
{
	std::cout << "Component Manager Created. \n";
}

ComponentManager::~ComponentManager()
{
	std::cout << "Component Manager Destroyed. \n";
	for (auto firstMap : MasterHash)
	{
		for (auto secondMap : MasterHash[firstMap.first])
		{
			delete MasterHash[firstMap.first][secondMap.first];
			MasterHash[firstMap.first][secondMap.first] = nullptr;
			MasterHash[firstMap.first].erase(secondMap.first);
		}
		MasterHash.erase(firstMap.first);
	}
};

ComponentManager &ComponentManager::_cmpManager()
{
	static ComponentManager ONLY_ONE;
	return ONLY_ONE;
}

//void ComponentManager::addComponent(std::string EntityName, Component &c)
//{
//	MasterHash[EntityName][typeid(c).name()] = c;
//}

void ComponentManager::deleteComponents(std::string entityName)
{
	MasterHash.erase(entityName);
}

void ComponentManager::changeName(const char *currentName, const char *newName)
{
	if (MasterHash.find(currentName) != MasterHash.end())
	{
		MasterHash[newName] = MasterHash[currentName];
		MasterHash.erase(currentName);
	}
}

bool ComponentManager::nameAvailable(std::string EntityName)
{
	if (MasterHash.find(EntityName) != MasterHash.end())
	{
		return false;
	}
	return true;
}