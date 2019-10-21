#pragma once
#include <unordered_map>
#include <functional>
#include "Events.h"
#include <mutex>

enum keycode 
{
	ONE=48,TWO=49,THREE=50, FOUR=51, FIVE=52, SIX=53, SEVEN=54, EIGHT=55, NINE=56, A=58, B=59,C=60,D=61,E=62,F=62,G=63,H=64,I=65,J=66,K=67,L=68,M=69,N=70,O=71,
	P=72, Q=73,R=74,S=75,T=76, U=77, V=78, W=79, X=80, Y=81, Z=82
};

class Keyboard 
{
public:
	Keyboard() {};
	~Keyboard() {};
	template<typename T>
	void setCallback(const keycode key, std::function<void(KeyEvent)> function, const T &object) 
	{
		std::lock_guard<std::mutex>lock(mutex);
		callbacks[keycode][&object] = function;
	}

	template<typename T>
	void removeCallback(const keycode key, const T &object)
	{
		std::lock_guard<std::mutex>lock(mutex);
		auto it = callbacks[key].find(&object);
		if (it != callbacks[key].end()) 
		{
			callbacks[key].erase(it);
		}
	}

	void call(const keycode key, const KeyEvent event)
	{
		std::lock_guard<std::mutex>lock(mutex);
		for (auto it : callbacks[key]) 
		{
			it.second(event);
		}
	}

private:
	std::unordered_map<keycode, std::unordered_map<int, std::function<void(const KeyEvent)>>> callbacks;
	mutable std::mutex mutex;
};