#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "Events.h"
#include <string>

class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();
	void OnClickSetFocus(LMouseDown *e);

private:
	std::string Focus = "";
};

#endif