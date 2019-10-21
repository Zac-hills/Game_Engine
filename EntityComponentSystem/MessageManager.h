#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__
#include <unordered_map>

class MsgManager
{
	typedef void(*func_ptr)(std::string);
	MsgManager();
	~MsgManager();
	MsgManager &getMsgManager();
	void translate(std::string);
	void callCommand(std::string func, std::string args);
	void read();

private:
	std::unordered_map<std::string, func_ptr> CommandList;
};


#endif