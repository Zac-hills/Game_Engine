#include "EventManager.h"
#include <typeinfo>

EventManager::EventManager(){}

EventManager::~EventManager(){}

void EventManager::HandleEvent(Event *e)
{
	ListenerStack[(typeid(e))]->exec(e);
}

void EventManager::AddListener(Event *e, baseListener *L)
{
	ListenerStack[typeid(e)] = L;
}