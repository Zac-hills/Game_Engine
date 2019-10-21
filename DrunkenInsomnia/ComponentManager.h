#pragma once
#include "Component.h"
#include <unordered_map>
#include<typeinfo>
#include <iostream>

class ComponentManager 
{
public:
	template<typename t>
	t& GetComponent(unsigned int a_EntityID) 
	{
		std::lock_guard<std::mutex> Lock(m_Mutex);
		if (auto &it = Map[a_EntityID].find(typeid(t)) != Map[a_EntityID].end())
		{
			return &it;
		}
		else 
		{
			std::cout << "Error Component Does not Exist \n";
			exit(-1);
		}
	}

	template<typename t>
	void AddComponent(unsigned int a_EntityID, t & a_Component)
	{
		std::lock_guard<std::mutex> Lock(m_Mutex);
		Map[a_EntityID][typeid(a_Component)] = a_Component;
	}

private:
	std::unordered_map<unsigned int, std::unordered_map<std::type_info, Component>> Map;
	std::mutex m_Mutex;
};