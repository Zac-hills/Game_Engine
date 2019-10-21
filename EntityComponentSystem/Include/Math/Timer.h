#ifndef  __TIMER_H__
#define __TIMER_H__
#define TIME Time::_time()
#include <unordered_map>

class Time
{
public:
	inline float time();
	float deltaTime();
	std::unordered_map<void *, float> m_dt_hashMap;
	static Time &_time();
private:
	Time();
};

#endif // ! __TIMER_H__