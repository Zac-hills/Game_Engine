#ifndef __INTERFACE_SQUARE_H__
#define __INTERFACE_SQUARE_H__
#include "Component.h"
#include "WindowManager.h"
#include "VectorMath.h"

class InterfaceSquareLayer : public Component
{
public:
	InterfaceSquareLayer(){};
	~InterfaceSquareLayer(){};
	//set pixel position(centre of interface)
	inline void setPosition(unsigned int a_x, unsigned int a_y)
	{
		//convert to screenSpace
		Pos.x = ((a_x / WINDOW_MANAGER.windowWidth) * 2.0f) - 1.0f;
		Pos.y = ((a_y / WINDOW_MANAGER.windowHeight) * 2.0f) - 1.0f;
	}
	//use this for dynamic resolution UI
	inline void setScreenSpacePosition(int a_x, int a_y) 
	{
		Pos.x = (float)a_x;
		Pos.y = (float)a_y;
	}
	//set pixel size of interface 
	inline void setSize(float a_Width, float a_Height)
	{
		//convert to screen space
		Size.x = ((a_Width / WINDOW_MANAGER.windowWidth) * 2.0f) - 1.0f;
		Size.y = ((a_Height / WINDOW_MANAGER.windowHeight) * 2.0f) - 1.0f;
	}
	//set screenSpace size of interface
	inline void setNormSize(float a_Width, float a_Height)
	{
		Size.x = (a_Width / 2.0f);
		Size.y = (a_Height / 2.0f);
	}

	vec2 Pos;
	vec2 Size;
private:

};

#endif