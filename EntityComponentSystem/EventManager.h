#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__
#define EVENT_MANAGER EventManager::getManager()
#include <unordered_map>
#include "Listener.h"
#include <typeindex>

class EventManager
{
public:

	void HandleEvent(Event *e);
	void AddListener(Event *e, baseListener *L);
	template<class T, class EventT>
	void AddListener(T *instance, void (T::*Memfunc)(EventT *e))
	{
		ListenerStack[typeid(EventT)] = new Listener<T, EventT>(instance, Memfunc);
	};
	template <class T>
	void AddEvent(T *a_t)
	{
		T *Ttemp = a_t;
		std::pair<std::type_index, T *> temp(typeid(T), Ttemp);
		EventStack.push_back(temp);

	};

	void ExecuteEvents()
	{
		for (unsigned int i = 0; i < EventStack.size(); i++)
		{
			try
			{
				ListenerStack.at(EventStack[i].first)->exec(EventStack[i].second);
			}
			catch (const std::out_of_range &oor)
			{
				continue;
			}

		}
		EventStack.clear();
	};

	static inline EventManager &getManager()
	{
		static EventManager ONLY_ONE;
		return ONLY_ONE;
	};

private:
	EventManager();
	~EventManager();
	std::unordered_map<std::type_index, baseListener *> ListenerStack;
	std::vector<std::pair<std::type_index, Event *>> EventStack;
};

#endif