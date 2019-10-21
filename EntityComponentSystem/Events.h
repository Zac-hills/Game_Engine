#ifndef __EVENTS_H__
#define __EVENTS_H__
#include "WindowManager.h"
#include <typeindex>
#include <string>

class Event
{
public:
	Event(){};
	~Event(){};
};

class Command : public Event
{
public:
	Command(std::string a_Command, std::string a_CurrentFocus) : CurrentCommand(a_Command), CurrentFocus(a_CurrentFocus){};
	~Command(){};
	std::string CurrentCommand = "";
	std::string CurrentFocus = "";
};

class LMouseDown : public Event 
{
public:
	LMouseDown(POINT *a_p) : p(a_p){};
	~LMouseDown(){};
	POINT *p = NULL;
};

class LMouseUp : public Event 
{
public:
	LMouseUp(POINT *a_p) : p(a_p){};
	~LMouseUp(){};
	POINT *p = NULL;
};

class RMouseDown : public Event 
{
public:
	RMouseDown(POINT *a_p) : p(a_p){};
	~RMouseDown(){};
	POINT *p = NULL;
};

class RMouseUp : public Event
{
public:
	RMouseUp(POINT *a_p) : p(a_p){};
	~RMouseUp(){};
	POINT *p = NULL;
};

#endif