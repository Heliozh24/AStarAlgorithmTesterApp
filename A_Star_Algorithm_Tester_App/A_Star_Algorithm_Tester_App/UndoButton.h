#pragma once
#include "Button.h"

class UndoButton: public Button
{
public:
	UndoButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText);
	void checkIfPressed(graphics::MouseState& mouse) override;
};