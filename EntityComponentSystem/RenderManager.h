#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__
#define RENDER_MANAGER RenderManager::getRenderManager()
#include <vector>
#include "Transform.h"
#include "Camera.h"
#include "FrameBuffer.h"

class RenderManager
{
private:
	typedef void (RenderManager::*func_ptr)(std::string);
	std::string currentCamera;
	RenderManager();
	~RenderManager();
	const int GL_TEXTURE_OFFSET = 33984;
	unsigned int currentTextureSize = 0;
	std::unordered_map<std::string, std::string> RenderList;
	std::unordered_map<std::string, std::string> AlphaRenderList;
	std::unordered_map <unsigned short, func_ptr> renderFunctions;

public:
	unsigned short renderStyle;
	unsigned int fullScreenQuadVAO;
	unsigned int fullScreenQuadVBO;
	FrameBuffer *DeferredBuffer;
	void init();
	void setRenderToLines();
	void setRenderToTriangles();
	void setRenderToPoints();
	void setCurrentCamera(std::string camera);
	std::string getCurrentCamera();
	static RenderManager &getRenderManager();
	void calcRenderList();
	void RenderScene();
	void BindMesh(std::string entity);
	void RenderMesh(std::string entity);
	void RenderTexture(std::string entity);
	void RenderTextureNormalMap(std::string entity);
	void RenderColorAttachment(unsigned int textureHandle);
	void renderInterfaceQuad(std::string e);
};




#endif