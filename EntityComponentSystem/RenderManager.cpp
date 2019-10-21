#include "ShaderManager.h"
#include "RenderManager.h"
#include "Entity.h"
#include "ComponentManager.h"
#include "Mesh.h"
#include "SceneGraphManager.h"
#include "Material.h"
#include "WindowManager.h"
#include "InterfaceSquareLayer.h"
#include "BufferManager.h"
#define BUFFER_OFFSET(i) (((char *)0 )+ i)


RenderManager::RenderManager()
{
	renderStyle = GL_TRIANGLES;
	//initialize function pointers
	renderFunctions[NULL_UNIFORM] = &RenderManager::RenderMesh;
	DeferredBuffer = new FrameBuffer(4);
	std::cout << "Render Manager Created. \n";
}

RenderManager::~RenderManager()
{
	std::cout << "Render Manager Destroyed. \n";
	delete DeferredBuffer;
}

void initFullScreenVbo()
{
	float VBO_DATA[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f
	};

	int vertexSize = 6 * 3 * sizeof(float);
	int texCoordSize = 6 * 2 * sizeof(float);

	glGenVertexArrays(1, &RENDER_MANAGER.fullScreenQuadVAO);
	glBindVertexArray(RENDER_MANAGER.fullScreenQuadVAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &RENDER_MANAGER.fullScreenQuadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, RENDER_MANAGER.fullScreenQuadVBO);

	glBufferData(GL_ARRAY_BUFFER, vertexSize + texCoordSize, VBO_DATA, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSize));

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

	glBindVertexArray(GL_NONE);
}

void RenderManager::init()
{
	initFullScreenVbo();
	DeferredBuffer->initBuffer();
	DeferredBuffer->initDepthTexture(WINDOW_MANAGER.windowWidth, WINDOW_MANAGER.windowHeight);
	DeferredBuffer->initColorTexture(0, WINDOW_MANAGER.windowWidth, WINDOW_MANAGER.windowHeight, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);//flat color
	DeferredBuffer->initColorTexture(1, WINDOW_MANAGER.windowWidth, WINDOW_MANAGER.windowHeight, GL_RGB8, GL_NEAREST, GL_CLAMP_TO_EDGE);//normal buffer
	DeferredBuffer->initColorTexture(2, WINDOW_MANAGER.windowWidth, WINDOW_MANAGER.windowHeight, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);//pos buffer
	DeferredBuffer->initColorTexture(3, WINDOW_MANAGER.windowWidth, WINDOW_MANAGER.windowHeight, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);//Selection Buffer
	DeferredBuffer->checkFBO();

	Entity *e = new Entity("Default_Camera");
	Transform *t = new Transform();
	t->m_position.position.z -= 15;
	CMP_MANAGER.addComponent(e->entityName, t);
	Camera *c = new Camera();
	c->perspectiveMatrix.perspectiveMatrix(1.0f, 2400.0f, 80.0f, 400, 400);
	CMP_MANAGER.addComponent(e->entityName, c);
	SceneNode sc(*t);
	SCENE_MANAGER.addSceneNode(sc, e->entityName);
	currentCamera = e->entityName;
}

RenderManager &RenderManager::getRenderManager()
{
	static RenderManager ONLY_ONE;
	return ONLY_ONE;
}

void RenderManager::setCurrentCamera(std::string camera)
{
	currentCamera = camera;
}

std::string RenderManager::getCurrentCamera()
{
	return currentCamera;
}
void RenderManager::calcRenderList()
{
	
}

void RenderManager::RenderScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	for (auto kv : RenderList)
	{
		CMP_MANAGER.getComponent<Material>(kv.first);
	}
	for (auto _pair : AlphaRenderList)
	{
		CMP_MANAGER.getComponent<Material>(_pair.first);
	}
}

void RenderManager::BindMesh(std::string entity)
{
	SHADER_MANAGER.sendToShader("frustrum", CMP_MANAGER.getComponent<Camera>(currentCamera)->perspectiveMatrix);
	SHADER_MANAGER.sendToShader("view", SCENE_MANAGER.sceneMap[currentCamera].m_globalTransform);
	SHADER_MANAGER.sendToShader("model", SCENE_MANAGER.sceneMap[entity].m_globalTransform);
	SHADER_MANAGER.sendToShader("unique_ID", CMP_MANAGER.getComponent<Entity>(entity)->rgb);
	glBindVertexArray(CMP_MANAGER.getComponent<Mesh>(entity)->mesh_ptr);
	glDrawArrays(renderStyle, 0, CMP_MANAGER.getComponent<Mesh>(entity)->mesh_size);
}

void RenderManager::RenderMesh(std::string e)
{
	DeferredBuffer->bind();
	SHADER_MANAGER.bindProgram(SHADER_MANAGER.Program_Hash[NULL_UNIFORM].Program_ptr);
	BindMesh(e);
	glBindVertexArray(0);
	glUseProgram(GL_NONE);
}

void RenderManager::RenderTexture(std::string e)
{
	SHADER_MANAGER.bindProgram(SHADER_MANAGER.Program_Hash[TEXTURE_UNIFORM].Program_ptr);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CMP_MANAGER.getComponent<Material>(e)->Texture_ptr);
	SHADER_MANAGER.sendToShader("frustrum", CMP_MANAGER.getComponent<Camera>(currentCamera)->perspectiveMatrix);
	SHADER_MANAGER.sendToShader("view", SCENE_MANAGER.sceneMap[currentCamera].m_globalTransform);
	SHADER_MANAGER.sendToShader("model", SCENE_MANAGER.sceneMap[e].m_globalTransform);
	SHADER_MANAGER.sendToShader("texture1", 0);
	glBindVertexArray(CMP_MANAGER.getComponent<Mesh>(e)->mesh_ptr);
	glDrawArrays(renderStyle, 0, CMP_MANAGER.getComponent<Mesh>(e)->mesh_size);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glBindVertexArray(0);
	glUseProgram(GL_NONE);
}

void RenderManager::RenderTextureNormalMap(std::string e)
{
	SHADER_MANAGER.bindProgram(SHADER_MANAGER.Program_Hash[TEXTURE_UNIFORM | NORMAL_MAP_UNIFORM].Program_ptr);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CMP_MANAGER.getComponent<Material>(e)->Texture_ptr);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, CMP_MANAGER.getComponent<Material>(e)->Normal_ptr);
	SHADER_MANAGER.sendToShader("frustrum", CMP_MANAGER.getComponent<Camera>(currentCamera)->perspectiveMatrix);
	SHADER_MANAGER.sendToShader("view", SCENE_MANAGER.sceneMap[currentCamera].m_globalTransform);
	SHADER_MANAGER.sendToShader("model", SCENE_MANAGER.sceneMap[e].m_globalTransform);
	SHADER_MANAGER.sendToShader("texture1", 0);
	SHADER_MANAGER.sendToShader("normalMap", 1);

	glBindVertexArray(CMP_MANAGER.getComponent<Mesh>(e)->mesh_ptr);
	glDrawArrays(renderStyle, 0, CMP_MANAGER.getComponent<Mesh>(e)->mesh_size);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glUseProgram(GL_NONE);
}

void RenderManager::RenderColorAttachment(unsigned int textureHandle)
{
	GLbitfield temp = 0;
	temp |= GL_DEPTH_BUFFER_BIT;
	glClear(temp);
	SHADER_MANAGER.bindProgram(SHADER_MANAGER.Program_Hash[FULL_SCREEN_UNIFORM | COLOR_ATTACHMENT_UNIFORM].Program_ptr);
	SHADER_MANAGER.sendToShader("texture1",  0);
	glBindVertexArray(fullScreenQuadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glBindVertexArray(0);
	glUseProgram(GL_NONE);
}

void RenderManager::setRenderToLines()
{
	renderStyle = GL_LINES;
}
void RenderManager::setRenderToTriangles()
{
	renderStyle = GL_TRIANGLES;
}
void RenderManager::setRenderToPoints()
{
	renderStyle = GL_POINTS;
}

void RenderManager::renderInterfaceQuad(std::string e)
{
	DeferredBuffer->bind();
	SHADER_MANAGER.bindProgram(SHADER_MANAGER.Program_Hash[INTERFACE_UNIFORM | TEXTURE_UNIFORM].Program_ptr);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CMP_MANAGER.getComponent<Material>(e)->Texture_ptr);
	SHADER_MANAGER.sendToShader("tex", 0);
	glBindTexture(GL_TEXTURE_2D, CMP_MANAGER.getComponent<Material>(e)->Texture_ptr);
	SHADER_MANAGER.sendToShader("unique_ID", CMP_MANAGER.getComponent<Entity>(e)->rgb);
	SHADER_MANAGER.sendToShader("Position", CMP_MANAGER.getComponent<InterfaceSquareLayer>(e)->Pos);
	SHADER_MANAGER.sendToShader("Size", CMP_MANAGER.getComponent<InterfaceSquareLayer>(e)->Size);
	glDrawArrays(GL_TRIANGLES, 0, 4);
	glUseProgram(GL_NONE);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);

}