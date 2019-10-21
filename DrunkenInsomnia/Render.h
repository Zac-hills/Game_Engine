#pragma once
#include "GL\glew.h"
#include <unordered_map>
#include "Images.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Events.h"

class Quad;
class InterfaceItem;

class Renderer 
{
public:
	Renderer();
	void CreateTextureID(Image &a_Image);
	void Render(Image &a_Image, Program &a_Prog);
	void Render(const Quad &a_Quad, Program &a_Prog);
	void Render(InterfaceItem &a_InterfaceItem, Program &a_Prog);
	void SetCamera(Camera &a_Camera);
	void GetPick(const MouseEvent& a_MouseEvent);
private:
	std::unordered_map<std::string, unsigned int>TextureMap;
	GLuint EmptyVAO;
	Camera *m_CurrentCamera;
	std::mutex m_Mutex;
};
