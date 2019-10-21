#include "File.h"

File::File(const std::string file)
{
	fileName = file;
	numOfBytes = 0;
}

File::File()
{
	numOfBytes = 0;
}

File::~File()
{
	if (file != nullptr) 
	{
		fclose(file);
	}
	if (fileBuffer != nullptr) 
	{
		delete[] fileBuffer;
	}
}

std::string File::getContents() 
{
	fseek(file, 0, SEEK_END);
	numOfBytes = ftell(file);

	fseek(file, 0, SEEK_SET);

	fileBuffer = new char[numOfBytes];
	std::size_t lengthRead = fread(fileBuffer, sizeof(char), numOfBytes, file);
	std::string result(fileBuffer, numOfBytes);
	delete[] fileBuffer;
	fileBuffer = nullptr;
	return result;
}

void File::close()
{
	fclose(file);
	file = nullptr;
}

bool File::open(const char* readOrWrite)
{
	fopen_s(&file, fileName.c_str(), readOrWrite);
	return (file != NULL);
}

bool File::open(const std::string & fileName, const char* readOrWrite)
{
	this->fileName = fileName;
	fopen_s(&file, fileName.c_str(), readOrWrite);
	return (file != NULL);
}

std::string File::getFileName() const
{
	return fileName;
}

const unsigned int File::numberOfBytes() const
{
	return numOfBytes;
}
