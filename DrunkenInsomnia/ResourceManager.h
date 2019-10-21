#pragma once
#include <unordered_map>

struct MeshInfo 
{
	unsigned int m_ID;
	unsigned int m_Size;
};

class ResourceManager 
{
public:

private:
	static std::unordered_map<std::string, MeshInfo> MeshID;
};