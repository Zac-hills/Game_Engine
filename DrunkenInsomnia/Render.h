#pragma once
#include "GL\glew.h"
#include <unordered_map>
#include "Images.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Events.h"
#include "FrameBuffer.h"

class Quad;
class InterfaceItem;

class Renderer 
{
public:
	Renderer();
	void createTextureID(Image &a_Image);
	void render(Image &a_Image, Program &a_Prog);
	void render(const Quad &a_Quad, Program &a_Prog);
	void render(InterfaceItem &a_InterfaceItem, Program &a_Prog);
	void setCamera(Camera &a_Camera);
	void getPick(const MouseEvent& a_MouseEvent);
	void addBuffer(const std::string &name, RenderBuffer &buffer);
	void renderBuffer(const std::string& name);

private:
	std::unordered_map<std::string, unsigned int>textureMap;
	GLuint emptyVAO;
	Camera *currentCamera;
	std::mutex mutex;
	Entity *selection = nullptr;
	FrameBuffer frameBuffer;
};
