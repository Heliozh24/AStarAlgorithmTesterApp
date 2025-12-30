#pragma once
#include <cmath>
class GridUtils
{
public:
	static inline int toGx(float x) { return int(std::round(x / 0.4f)); } // converts float x to int x
	static inline int toGy(float y) { return int(std::round((y - 2.0f) / 0.6f)); } // converts float y to int y(subtracing with 2.0 because we start from y=2)
};