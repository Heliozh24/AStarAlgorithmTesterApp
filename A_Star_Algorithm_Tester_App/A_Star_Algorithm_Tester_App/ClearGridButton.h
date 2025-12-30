#pragma once
#include "Button.h"

class ClearGridButton : public Button
{
public:
	ClearGridButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText);
	void checkIfPressed(graphics::MouseState& mouse) override;
};