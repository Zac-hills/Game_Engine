#pragma once
#include <queue>
#include <mutex>

class UniqueIdentifier 
{
public:
	UniqueIdentifier() {};

	void ReleaseID(unsigned int ID) 
	{
		std::lock_guard<std::mutex> l(m_Mutex);
		AvailableIDS.push(ID);
	}

	unsigned int GetID() 
	{
		if (!AvailableIDS.size())
		{
			return ++Counter;
		}
		std::lock_guard<std::mutex> l (m_Mutex);
		unsigned int l_cache = AvailableIDS.front();
		AvailableIDS.pop();
		return l_cache;
	}
private:
	std::queue<unsigned int> AvailableIDS;
	unsigned int Counter = 0;
	std::mutex m_Mutex;
};