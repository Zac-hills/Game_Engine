#ifndef _CMP_MANAGER_H_
#define _CMP_MANAGER_H_
#include <unordered_map>
#include "Component.h"
#define CMP_MANAGER ComponentManager::_cmpManager()
#include "Entity.h"


class ComponentManager
{
private:

public:
	ComponentManager();
	~ComponentManager();
	std::vector<Component>ComponentContainer;
	std::vector<Entity>EntityContainer;
	std::unordered_map<std::string, std::unordered_map<std::string, Component *>> MasterHash;
	std::unordered_map<std::string, std::string> renderEntities;
	std::unordered_map<std::string, std::string> renderAlphaEntities;
	static ComponentManager &_cmpManager();
	template <typename T>
	T* getComponent(std::string entityName)
	{
		if (MasterHash.find(entityName) != MasterHash.end())
		{
			std::string test = typeid(T).name();
			return static_cast<T*>(MasterHash[entityName][typeid(T).name()]);
		}
		else
		{
			std::cout << "Error getting Component \n";
			exit(124);
		}
	}

	template<typename T>
	void deleteComponent(std::string entityName)
	{
		if (MasterHash[entityName].find(typeid(T).name()) != MasterHash[entityName].end())
		{
			MasterHash[entityName].erase(typeid(T).name());
		}
	}
	template<typename T>
	void containsComponent(std::string entityName)
	{
		if (MasterHash[entityName].find(typeid(T).name()) != MasterHash[entityName].end())
		{
			return true;
		}
		return false;
	}
	void deleteComponents(std::string entityName);
	void changeName(const char *currentName, const char *newName);
	template<typename T = Component *>
	void addComponent(std::string entityName, T *c)
	{
		MasterHash[entityName][typeid(T).name()] = c;
	}
	bool nameAvailable(std::string entityName);
};

#endif