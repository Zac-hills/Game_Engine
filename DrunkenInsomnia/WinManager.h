#pragma once
#include <windows.h>
#include <string>
#include "Keyboard.h"
#include "Mouse.h"

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
	std::mutex mutex;
public:
	Keyboard keyboard;
	Mouse mouse;
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
	void handleWindowMessages();
	
	static windowManager &getWindowManager();
};