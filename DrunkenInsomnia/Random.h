#pragma once
#include <cmath>

int Random(const int min, const int max)
{
	return rand() % max + min;
}

unsigned int Random(const unsigned int min, const unsigned int max)
{
	return rand() % max + min;
}

float Random(const float min, const float max)
{
}