#pragma once
#include "VectorMath.h"
#include "Entity.h"
#include "Array.h"

class InterfaceItem : public Entity
{
	friend class Renderer;
public:
	InterfaceItem();
	//Size in pixels, position in pixels, position is center of quad
	InterfaceItem(const vec2 &a_Size, const vec2 &a_Pos);
	unsigned int GetTextureID() const;
	void SetTextureID(unsigned int a_TextureID);
	void SetSize(const vec2 &a_Size);
	void SetPosition(const vec2 &a_Postion);
	Array<vec2> GetVertices() const;
	Array<vec2> GetUV() const;
	void OnClick();
private:
	void SetBuffer();
	vec2 m_Size;
	vec2 m_Position;
	//default texture is 1
	unsigned int m_TextureID = 1;
	Array<vec2> Vertices;
	Array<vec2> UVCoordinates;
	mutable std::mutex m_Mutex;
};