#pragma once
#include "Button.h"
#include "AStarAlgorithm.h"

class StartTestButton: public Button
{
public:
	StartTestButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText);
	void checkIfPressed(graphics::MouseState& mouse) override;
};