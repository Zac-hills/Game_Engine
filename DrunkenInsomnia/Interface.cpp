#include "Interface.h"
#include "WinManager.h"

InterfaceItem::InterfaceItem() : Entity(), Vertices(6), UVCoordinates(6) 
{
	UVCoordinates[0] = vec2(0, 0);
	UVCoordinates[1] = vec2(1, 0);
	UVCoordinates[2] = vec2(0, 1);
	UVCoordinates[3] = vec2(1, 1);
	UVCoordinates[4] = vec2(0, 1);
	UVCoordinates[5] = vec2(1, 0);
}

InterfaceItem::InterfaceItem(const vec2 &a_Size, const vec2 &a_Pos) : Entity(), Vertices(6), UVCoordinates(6)
{
	m_Size = a_Size;
	m_Position = a_Pos;
	SetBuffer();
	UVCoordinates[0] = vec2(0, 0);
	UVCoordinates[1] = vec2(1, 0);
	UVCoordinates[2] = vec2(0, 1);
	UVCoordinates[3] = vec2(1, 1);
	UVCoordinates[4] = vec2(0, 1);
	UVCoordinates[5] = vec2(1, 0);
}

void  InterfaceItem::SetBuffer() 
{
	unsigned int l_Height = windowManager::getWindowManager().windowHeight;
	unsigned int l_Width = windowManager::getWindowManager().windowWidth;
	std::lock_guard<std::mutex> Lock(m_Mutex);
	vec2 l_Position(m_Position.x / l_Width, m_Position.y / l_Height);
	vec2 l_Size(m_Size.x / l_Width, m_Size.y / l_Height);

	l_Position.x *= 2.0f;
	l_Position.x -= 1.0f;
	
	l_Position.y *= 2.0f;
	l_Position.y -= 1.0f;

	Vertices[0] = vec2(l_Position.x - l_Size.x, l_Position.y - l_Size.y);
	Vertices[1] = vec2(l_Position.x + l_Size.x, l_Position.y - l_Size.y);
	Vertices[2] = vec2(l_Position.x - l_Size.x, l_Position.y + l_Size.y);
	Vertices[3] = vec2(l_Position.x + l_Size.x, l_Position.y + l_Size.y);
	Vertices[4] = vec2(l_Position.x - l_Size.x, l_Position.y + l_Size.y);
	Vertices[5] = vec2(l_Position.x + l_Size.x, l_Position.y - l_Size.y);
}

void InterfaceItem::SetTextureID(unsigned int a_TextureID) 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_TextureID = a_TextureID;
}

unsigned int InterfaceItem::GetTextureID() const
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return m_TextureID; 
}

void InterfaceItem::SetSize(const vec2 &a_Size) 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Size = a_Size;
	SetBuffer();
}

void InterfaceItem::SetPosition(const vec2 &a_Position)
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	m_Position = a_Position;
	SetBuffer();
}

void InterfaceItem::OnClick() 
{
	
}

Array<vec2> InterfaceItem::GetVertices() const 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return Vertices;
}

Array<vec2> InterfaceItem::GetUV() const 
{
	std::lock_guard<std::mutex> Lock(m_Mutex);
	return UVCoordinates;
}