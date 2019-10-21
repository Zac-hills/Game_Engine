#include "Timer.h"
#include <ctime>

float Timer::m_DeltaTime = 0.0f;
float Timer::m_PreviousTime = 0.0f;

Timer::Timer(){}

float Timer::time()
{
	return (std::clock() / (float)CLOCKS_PER_SEC);
}

float Timer::getDeltaTime() const
{
	return m_DeltaTime;
}

void Timer::CalculateDeltaTime() 
{
	m_DeltaTime = time() - m_PreviousTime;
}

void Timer::restart() 
{
	m_StartTime = time();
}

float Timer::getTime() const 
{
	return time() - m_StartTime;
}