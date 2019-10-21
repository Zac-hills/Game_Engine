#ifndef __WINDOWS_MANAGER_H__
#define __WINDOWS_MANAGER_H__
#define WINDOW_MANAGER windowManager::getWindowManager()
#include "glew.h"
#include "wglew.h"
#include <windows.h>  
#include <vector>

class RMouseDown;

struct MenuOptions
{
	std::vector<std::string> Options;
};

class windowManager
{
private:
	windowManager();
	~windowManager();
	
	HGLRC hRC = NULL;					// Holds The Instance Of The Application
	HDC hDC = NULL;                           // Private GDI Device Context
	HINSTANCE hInstance;				// Holds The Instance Of The Application
	bool fullscreen = false;
	HWND consoleHwnd = NULL;
	MenuOptions menuOptions;

public:
	HMENU contextMenu = NULL;
	HWND hWnd = NULL;   
	unsigned int windowWidth;
	unsigned int windowHeight;
	bool keys[256];			// Array Used For The Keyboard Routine
	bool active = true;
	POINT getMouseWindowCoords();
	POINT getMouseScreenCoords();
	void setConsoleWindow(HWND ptr);
	void resizeWindow(unsigned int width, unsigned int height);
	bool createWindow(char* title, unsigned int width, unsigned int height, int bits, bool fullscreenflag);
	void destroyWindow();
	void swapBuffers();
	void initGL();
	void CreatePopUpMenu(RMouseDown *e);
	void AddMenuOptions(std::string s);
	bool RemoveMenuOptions(std::string s);
	void SetMenu(MenuOptions *a_MO);
	static windowManager &getWindowManager();
};



#endif