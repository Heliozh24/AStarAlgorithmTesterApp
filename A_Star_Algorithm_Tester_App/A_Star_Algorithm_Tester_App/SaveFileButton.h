#pragma once
#include "Button.h"

class SaveFileButton : public Button
{
public:
	SaveFileButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText);
	void checkIfPressed(graphics::MouseState& mouse) override;
};