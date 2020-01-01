#pragma once
#include <iostream>
#define LOG(data) Logger::log(data, __LINE__, __FILE__)

class Logger 
{
public:
	template<typename t>
	static void log(const t& data, unsigned int line, const char* file) 
	{
		std::cout << "[" << line << "]" << "(" << file << "): " << data << std::endl;
	}
private:
};