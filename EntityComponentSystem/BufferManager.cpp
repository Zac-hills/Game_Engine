#include "BufferManager.h"
#include "glew.h"
#include <iostream>

BufferManager::BufferManager()
{
	std::cout << "Buffer Manager Created. \n";
}

BufferManager::~BufferManager()
{
	std::cout << "Buffer Manager Destroyed. \n";
}

BufferManager &BufferManager::getBufferManager()
{
	static BufferManager ONLY_ONE;
	return ONLY_ONE;
}

unsigned int BufferManager::checkIfExists(const char *filePath)
{
	if (Buffer_Hash.find(filePath) != Buffer_Hash.end())
	{
		Buffer_Hash[filePath].reference_count++;
		return Buffer_Hash[filePath].buffer_ptr;
	}
	return 0;
}

void BufferManager::removeReference(const char *filePath)
{
	if (Buffer_Hash.find(filePath) != Buffer_Hash.end())
	{
		Buffer_Hash[filePath].reference_count --;
		if (Buffer_Hash[filePath].reference_count <= 0)
		{
			unsigned int cache = Buffer_Hash[filePath].buffer_ptr;
			glDeleteBuffers( 1 , &Buffer_Hash[filePath].buffer_ptr);
			glDeleteVertexArrays(1,  &cache);
			Buffer_Hash.erase(filePath);
		}
	}
}

void BufferManager::addBuffer(const char *filePath, unsigned int buffer_ptr)
{
	BufferInfo temp;
	temp.buffer_ptr = buffer_ptr;
	temp.buffer_size = 0;
	temp.reference_count = 1;
	Buffer_Hash[filePath] = temp;
}

void BufferManager::addBuffer(const char *filePath,unsigned int buffer_ptr, unsigned int buffer_size)
{
	BufferInfo temp;
	temp.buffer_ptr = buffer_ptr;
	temp.buffer_size = buffer_size;
	temp.reference_count = 1;
	Buffer_Hash[filePath] = temp;
}

unsigned int BufferManager::getBufferSize(const char *filePath)
{
	if (Buffer_Hash.find(filePath) != Buffer_Hash.end())
	{
		return Buffer_Hash[filePath].buffer_size;
	}
	return 0;
}