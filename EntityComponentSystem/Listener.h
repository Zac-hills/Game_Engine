#ifndef __LISTENER_H__
#define __LISTENER_H__
#include "Events.h"

class baseListener
{
public:
	virtual ~baseListener(){};
	void exec(Event *event)
	{
		call(event);
	}
private:
	virtual void call(Event *) = 0;
};


template <class T, class EventT>
class Listener : public baseListener
{
public:
	typedef void(T::*MemFunc)(EventT*);
	Listener(T *instance, MemFunc memFn) : instance(instance), memFunc(memFn){};

	void call(Event *a_event)
	{
		EventT *temp = static_cast<EventT *>(a_event);
		(instance->*memFunc)(static_cast<EventT *>(a_event));
	}

private:
	T *instance;
	MemFunc memFunc;
};

#endif