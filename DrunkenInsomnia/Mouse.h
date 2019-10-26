#pragma once
#include"Events.h"
#include<functional>
#include <mutex>

class Mouse 
{
public:
	template<typename T>
	void subscribeLeftClickUp(std::function<void(const MouseEvent&)> function,const T& object) 
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::LEFT_UP]);
		leftClickUp[(int)&object] = function;
	}
	template<typename T>
	void unsubscribeLeftClickUp(const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::LEFT_UP]);
		if (leftClickUp.find(((int)&object)) != leftClickUp.end())
		{
			leftClickUp.erase((int)&object);
		}
	}
	template<typename T>
	void subscribeLeftClickDown(std::function<void(const MouseEvent&)> function, const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::LEFT_DOWN]);
		leftClickDown[(int)&object] = function;
	}
	template<typename T>
	void unsubscribeLeftClickDown(const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::LEFT_DOWN]);
		if (leftClickDown.find((int)&object) != leftClickDown.end())
		{
			leftClickDown.erase((int)&object);
		}
	}
	template<typename T>
	void subscribeRightClickUp(std::function<void(const MouseEvent&)> function, const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::RIGHT_UP]);
		rightClickDown[(int)&object] = function;
	}
	template<typename T>
	void subscribeRightClickDown(std::function<void(const MouseEvent&)> function, const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::RIGHT_DOWN]);
		rightClickUp[(int)&object] = function;
	}

	template<typename T>
	void subscribeMiddleClick(std::function<void(const MouseEvent&)> function, const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::MIDDLE]);
		middle[(int)&object] = function;
	}
	template<typename T>
	void subscribeScroll(std::function<void(const MouseEvent&)> function, const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::SCROLL]);
		scroll[(int)&object] = function;
	}
	template<typename T>
	void subscribeMove(std::function<void(const MouseEvent&)> function, const T& object)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::MOVE]);
		move[(int)&object] = function;
	}

	void callMove(const MouseEvent& event) 
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::MOVE]);
		auto &it= move.begin();
		while (it != move.end())
		{
			auto next = std::next(it, 1);
			it->second(event);
			it = next;
		}
	}
	void callScroll(const MouseEvent& event)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::SCROLL]);
		auto &it=scroll.begin();
		while (it != scroll.end())
		{
			auto next = std::next(it, 1);
			it->second(event);
			it = next;
		}
	}
	void callLeftClickUp(const MouseEvent& event)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::LEFT_UP]);
		auto &it =leftClickUp.begin();
		while (it != leftClickUp.end())
		{
			auto next = std::next(it, 1);
			it->second(event);
			it = next;
		}
	}
	void callLeftClickDown(const MouseEvent& event)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::LEFT_DOWN]);
		auto &it = leftClickDown.begin();
		while(it !=leftClickDown.end())
		{
			auto next = std::next(it, 1);
			it->second(event);
			it = next;
		}
	}
	void callRightClickUp(const MouseEvent& event)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::RIGHT_UP]);
		auto &it= rightClickUp.begin();
		while (it != rightClickUp.end())
		{
			auto next = std::next(it, 1);
			it->second(event);
			it = next;
		}
	}
	void callRightClickDown(const MouseEvent& event)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex[container::RIGHT_DOWN]);
		auto &it =rightClickDown.begin();
		while (it != rightClickUp.end())
		{
			auto next = std::next(it, 1);
			it->second(event);
			it = next;
		}
	}

private:
	enum container
	{
		LEFT_DOWN = 0, LEFT_UP=1, RIGHT_DOWN = 2, RIGHT_UP=3, SCROLL = 4, MOVE = 5, MIDDLE=6
	};
	std::recursive_mutex mutex[7];
	std::unordered_map<int, std::function<void(const MouseEvent&)>> leftClickUp;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> rightClickUp;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> leftClickDown;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> rightClickDown;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> scroll;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> move;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> middle;
};