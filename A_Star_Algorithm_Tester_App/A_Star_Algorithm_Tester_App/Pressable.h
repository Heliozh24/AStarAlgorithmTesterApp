#pragma once
#include <sgg/graphics.h>

class Pressable
{
public:

	virtual void checkIfPressed(graphics::MouseState& mouse) = 0;
	virtual ~Pressable() {};
};