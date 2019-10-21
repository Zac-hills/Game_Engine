#pragma once
#include "VectorMath.h"
#include <list>
#include <unordered_map>
#include <cmath>
#include <mutex>

template<typename t>
class Grid 
{
public:

	void push(t &element) 
	{
		std::lock_guard<std::mutex> lock(mutex);
		data.push_back(element);
	}

	void pop(t &element) 
	{
		std::lock_guard<std::mutex> lock(mutex);
		data.remove(element);
	}

private:
	std::mutex mutex;
	std::list<t &> data;
};

template<typename t>
class SpatialGrid 
{
public:
	SpatialGrid(vec2 topLeft, vec2 bottomRight, int interval) 
	{
		float minX = fmin(bottomRight.x, topLeft.x);
		float maxX = fmax(bottomRight.x, topLeft.x);
		float minY = fmin(bottomRight.y, topLeft.y);
		float maxY = fmax(bottomRight.y, topLeft.y);
		min.x = minX;
		min.y = minY;
		this->interval = interval;
		for (int x = (int)maxX; x < (int)(minX - interval); x -= interval) 
		{
			for (int y = (int)maxY; y < (int)(minY = interval); y -= interval) 
			{
				grid[std::pair<x, y>] = Grid<t>();
			}
		}
	}

	~SpatialGrid() {};

	Grid<t>operator[](const vec2& position) 
	{
		std::lock_guard<std::mutex>lock(mutex);
		return grid[std::pair<int, int>((int)((position.x - min.x) / interval), (int)((position.y - min.y) / interval))];
	}



private:
	std::mutex mutex;
	std::unordered_map<std::pair<int, int>, Grid<t>> grid;
	int interval;
	vec2 min;
};