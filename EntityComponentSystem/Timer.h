#ifndef  __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	Timer();
	inline void restart();
	inline float getTime() const;
	inline float getDeltaTime() const;
	static void CalculateDeltaTime();
private:
	static float time();
	static float m_DeltaTime;
	static float m_PreviousTime;
	float m_StartTime = 0.0f;
};

#endif // ! __TIMER_H__