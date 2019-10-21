#pragma once
#include <string>
#include <stdio.h>

class File 
{
public:
	//requires relative or absolute path
	File(const std::string file);
	File();
	~File();
	std::string getContents();
	void close();
	//"w" or "r"
	bool open(const char * readOrWrite);
	bool open(const std::string &fileName,const char* readOrWrite);
	std::string getFileName() const;
	const unsigned int numberOfBytes() const;
private:
	char *fileBuffer=nullptr;
	std::string fileName;
	FILE *file=nullptr;
	unsigned int numOfBytes;
};