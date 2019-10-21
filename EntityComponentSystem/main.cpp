#include "glew.h"
#include "Entity.h"
#include "dirent.h"
#include <string>
#include "MeshLoader.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "SceneGraphManager.h"
#include "WindowManager.h"
#include "Wrapper.h"
#include "RenderManager.h"
#include "ShaderManager.h"
#include "Timer.h"
#include "InterfaceManager.h"
#include "EventManager.h"
#include "InterfaceSquareLayer.h"

int main()
{
	//glewInit();
	InterfaceManager IM;
	EventManager::getManager().AddListener<InterfaceManager, LMouseDown>(&IM, &InterfaceManager::OnClickSetFocus);
	windowManager::getWindowManager().createWindow("test", 1920, 720, 32, false);
	// WINDOW_MANAGER.setConsoleWindow(GetConsoleWindow());
	createNewEntity("Grid");
	addMesh("Grid");
	changeMeshPath("Grid", "./Assets/Meshes/Grid.obj");
	createNewEntity("Sphere");
	addMesh("Sphere");
	changeMeshPath("Sphere", "./Assets/Meshes/SphereTri.obj");
	addMaterial("Sphere");
	createNewEntity("Sphere1");
	addMesh("Sphere1");
	changeMeshPath("Sphere1", "./Assets/Meshes/SphereTri.obj");
	//createNewEntity("TestInterface");
	//addSquareInterface("TestInterface");
	//addMaterial("TestInterface");
	//changeMaterialTexturePath("TestInterface", "./Assets/Materials/hd-wallpaper-1080p-widescreen-1080p-backgrounds.jpg");
	//CMP_MANAGER.getComponent<InterfaceSquareLayer>("TestInterface")->setNormSize(0.0, 0.0);
	//CMP_MANAGER.getComponent<InterfaceSquareLayer>("TestInterface")->setPosition(0, 0);
	SCENE_MANAGER.sceneMap["Sphere1"].m_transform->m_position.position.x += 10;
	SCENE_MANAGER.changeParent("Sphere1", "Sphere");
	SHADER_MANAGER.loadStandardShaders();
	RENDER_MANAGER.init();
	glEnable(GL_DEPTH_TEST);
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);
		MSG		msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				exit(0);						// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		SCENE_MANAGER.update();
		if (windowManager::getWindowManager().keys[VK_DOWN])
		{
			SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position.position.z -= 1.01f;
		}
		if (windowManager::getWindowManager().keys[VK_RIGHT])
		{
			SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position.position.x += 1.01f;
		}
		if (windowManager::getWindowManager().keys[VK_LEFT])
		{
			SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position = SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position.rotateY(1.0f);
		}
		if (windowManager::getWindowManager().keys[VK_UP])
		{
			SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position = SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position.rotateX(0.9f);
			SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position.position.z += 1.01f;
		}
		if (windowManager::getWindowManager().keys['w'])
		{
			SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position = SCENE_MANAGER.sceneMap[RENDER_MANAGER.getCurrentCamera()].m_transform->m_position.rotateX(0.9f);
		}
		EventManager::getManager().ExecuteEvents();
		RENDER_MANAGER.DeferredBuffer->clear();
		RENDER_MANAGER.RenderMesh("Sphere");
		RENDER_MANAGER.RenderMesh("Sphere1");
		//RENDER_MANAGER.renderInterfaceQuad("TestInterface");
		RENDER_MANAGER.setRenderToLines();
		RENDER_MANAGER.RenderMesh("Grid");
		RENDER_MANAGER.setRenderToTriangles();
		RENDER_MANAGER.RenderColorAttachment(RENDER_MANAGER.DeferredBuffer->getColorHandle(0));
		RENDER_MANAGER.DeferredBuffer->moveToBackBuffer(WINDOW_MANAGER.windowWidth, WINDOW_MANAGER.windowHeight);
		windowManager::getWindowManager().swapBuffers();
	}
	return 0;
}