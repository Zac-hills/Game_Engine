#pragma once
#include"Events.h"
#include<functional>
#include <mutex>

class Mouse 
{
public:
	template<typename T>
	void subscribeLeftClickUp(std::function<void(const MouseEvent&)> function, T& object) 
	{
		std::lock_guard<std::mutex> lock(mutex[container::LEFT]);
		leftClick[&object] = function;
	}
	template<typename T>
	void subscribeLeftClickDown(std::function<void(const MouseEvent&)> function, T& object)
	{
		std::lock_guard<std::mutex> lock(mutex[container::LEFT]);
		leftClick[&object] = function;
	}
	template<typename T>
	void subscribeRightClickUp(std::function<void(const MouseEvent&)> function, T& object)
	{
		std::lock_guard<std::mutex> lock(mutex[container::RIGHT]);
		rightClick[&object] = function;
	}
	template<typename T>
	void subscribeRightClickDown(std::function<void(const MouseEvent&)> function, T& object)
	{
		std::lock_guard<std::mutex> lock(mutex[container::RIGHT]);
		rightClick[&object] = function;
	}
	template<typename T>
	void subscribeMiddleClick(std::function<void(const MouseEvent&)> function, T& object)
	{
		std::lock_guard<std::mutex> lock(mutex[container::MIDDLE]);
		middle[&object] = function;
	}
	template<typename T>
	void subscribeScroll(std::function<void(const MouseEvent&)> function, T& object)
	{
		std::lock_guard<std::mutex> lock(mutex[container::SCROLL]);
		scroll[&object] = function;
	}
	template<typename T>
	void subscribeMove(std::function<void(const MouseEvent&)> function, T& object)
	{
		std::lock_guard<std::mutex> lock(mutex[container::MOVE]);
		move[object] = function;
	}

	void callMove(const MouseEvent& event) 
	{
		std::lock_guard<std::mutex> lock(mutex[container::MOVE]);
		for (auto& it : move) 
		{
			it.second(event);
		}
	}
	void callScroll(const MouseEvent& event)
	{
		std::lock_guard<std::mutex> lock(mutex[container::SCROLL]);
		for (auto& it : scroll)
		{
			it.second(event);
		}
	}
	void callLeftClickUp(const MouseEvent& event)
	{
		std::lock_guard<std::mutex> lock(mutex[container::LEFT]);
		for (auto& it : leftClickUp)
		{
			it.second(event);
		}
	}
	void callLeftClickDown(const MouseEvent& event)
	{
		std::lock_guard<std::mutex> lock(mutex[container::LEFT]);
		for (auto& it : leftClickDown)
		{
			it.second(event);
		}
	}
	void callRightClickUp(const MouseEvent& event)
	{
		std::lock_guard<std::mutex> lock(mutex[container::RIGHT]);
		for (auto& it : rightClickUp)
		{
			it.second(event);
		}
	}
	void callRightClickDown(const MouseEvent& event)
	{
		std::lock_guard<std::mutex> lock(mutex[container::RIGHT]);
		for (auto& it : rightClickDown)
		{
			it.second(event);
		}
	}

private:
	enum container
	{
		LEFT = 0, RIGHT = 1, SCROLL = 2, MOVE = 3, MIDDLE=4
	};
	std::mutex mutex[5];
	std::unordered_map<int, std::function<void(const MouseEvent&)>> leftClickUp;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> rightClickUp;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> leftClickDown;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> rightClickDown;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> scroll;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> move;
	std::unordered_map<int, std::function<void(const MouseEvent&)>> middle;
};