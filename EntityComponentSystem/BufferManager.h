#ifndef __BUFFER_MANAGER_H__
#define __BUFFER_MANAGER_H__
#define BUFFER_MANAGER BufferManager::getBufferManager()
#include <unordered_map>


struct BufferInfo
{
	unsigned int buffer_ptr;
	unsigned int buffer_size;
	unsigned int reference_count;
};

class BufferManager
{
private:
	BufferManager();
	~BufferManager();
	std::unordered_map<std::string, BufferInfo> Buffer_Hash;

public:
	static BufferManager &getBufferManager();
	unsigned int checkIfExists(const char *);
	void removeReference(const char *);
	void addBuffer(const char *, unsigned int buffer_ptr);
	void addBuffer(const char *, unsigned int buffer_ptr, unsigned int buffer_size);
	unsigned int getBufferSize(const char *);
	std::unordered_map<unsigned int, std::string> EntityIDs;
};


#endif