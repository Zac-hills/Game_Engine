#pragma once
#include "VectorMath.h"

class Event
{
public:
private:
};

class MouseEvent : public Event 
{
public:
	MouseEvent(const unsigned int a_x, const unsigned int a_y)
	{
		position[0] = a_x;
		position[1] = a_y;
	}
	unsigned int GetX() const { return position[0]; }
	unsigned int GetY() const { return position[1]; }
private:
	unsigned int position[2];
};

class KeyEvent : public Event 
{
public:
	enum KeyState
	{
		UP,  DOWN, HOLD
	};
	KeyEvent(const KeyState state) : state(state){}
private:
	KeyState state;
};