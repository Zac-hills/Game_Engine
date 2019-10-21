#include "MessageManager.h"
#include <iostream>
#include <string>
#include "dirent.h"

MsgManager::MsgManager(){}

MsgManager::~MsgManager(){}

MsgManager &MsgManager::getMsgManager()
{
	static MsgManager ONLY_ONE;
	return ONLY_ONE;
}

void MsgManager::translate(std::string s)
{
	unsigned int split = s.find_first_of("|");
	std::string function = s.substr(0, split + 1);
	callCommand(function, s.substr(split + 1));
}

void MsgManager::callCommand(std::string func, std::string args)
{
	if (CommandList.find(func) != CommandList.end())
	{
		CommandList[func](args);
	}
	else
	{
		std::cout << "Command call: " << func << " is not a recognized Command." << std::endl;
	}
}

void MsgManager::read()
{
	DIR *directory;
	directory = opendir("./assets/");
	struct dirent *entry;

	if (!directory)
	{
		std::cout << "Could not find asset folder. \n";
		return;
	}

	int i = 0;
	std::vector<std::string> FolderBuffer;
	while ((entry = readdir(directory)) != NULL)
	{
		std::string selection;
		selection = i;
		selection += ": ";
		selection += entry->d_name;
		FolderBuffer.push_back(entry->d_name);
		std::cout << selection << std::endl;
		i++;
	}
	std::cout << "Choose a file or folder.\n";
	unsigned int value;
	std::string command;
	value = FolderBuffer.size() + 1;
	while (value > FolderBuffer.size())
	{
		std::cin >> value;
	}
	std::cout << "What command to do with this file or folder?\n";
	std::cin >> command;

	command += FolderBuffer[value];
	translate(command);
}