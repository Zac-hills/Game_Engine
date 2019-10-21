#include "WinManager.h"
#include "Include\GL\glew.h"
#include "IO.h"
#include "Include\CompilerInterface.h"
#include "ScriptManager.h"
#include "TaskManager.h"
#include "Quaternions.h"
#include "ShaderManager.h"
#include "Render.h"
#include "Physics.h"
#include "Renderables.h"
#include "Interface.h"
#include "FrameBuffer.h"
#include "TaskManager.h"
#include "File.h"

TaskManager tk;

void MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void Init() 
{
	windowManager::getWindowManager().createWindow("test", 1920, 720, 32, false);
	GLenum check = glewInit();
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback((GLDEBUGPROC)MessageCallback, 0);	
	FreeImage_Initialise();
}

void print(int i) 
{
	std::cout << i << std::endl;
}

int main()
{
	File file("./Shaders/VertexShader/FullScreenQuad.vert");
	file.open("rb");
	std::cout << file.getContents() << std::endl;
	//while (true) 
	//{
	//	Sleep(10);
	//	Task<int> *task = new Task(10);
	//	task->function = std::bind(&print, std::placeholders::_1);
	//	tk.addTask(*task);
	//}
	Init();
	FrameBuffer fb;
	ColorBufferRGB16 renderBuffer(300,300);
	fb.AddBuffer("Color",renderBuffer);
	InterfaceItem If(vec2(960, 360), vec2(960,360));
	VertexShader vs = Load<VertexShader>("FullScreenQuad.vert");
	FragmentShader fs = Load<FragmentShader>("Texture.frag");
	VertexShader vs1 = Load<VertexShader>("Interface.vert");
	FragmentShader fs1 = Load<FragmentShader>("Texture.frag");
	
	Program pp;
	pp.AddShader(fs);
	pp.AddShader(vs);
	ShaderManager::CreateProgram(pp);
	
	Program pp1;
	pp1.AddShader(vs1);
	pp1.AddShader(fs1);
	ShaderManager::CreateProgram(pp1);
	//ScriptManager::NewScript("TestScript");
	//CompilerInterface::Compiler::Compile("D:\\Desktop\\Repositories\\ECS\\DrunkenInsomnia\\Bin\\VsDevCmd.bat", "cl /D_USRDLL /D_WINDLL D:\\Desktop\\Repositories\\ECS\\DrunkenInsomnia\\Scripts\\TestScript.cpp /MT /link /DLL /OUT:Bin\\TestScript.dll");
	
	Renderer r;
	Image p = Load<Image>("./Capture.PNG");
	r.CreateTextureID(p);
	If.SetTextureID(p.m_ID);
	glEnable(GL_DEPTH_TEST);
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);
		//r.Render(p, pp);
		r.Render(If, pp1);
		windowManager::getWindowManager().swapBuffers();
		windowManager::getWindowManager().handleWindowMessages();
	}
	return 0;
}