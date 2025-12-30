#pragma once
#include <sgg/graphics.h>
#include "Button.h"
#include <string>

class ChoiceButton : public Button
{
protected:
	static float activeChoiceButtonX;
	static float activeChoiceButtonY;
	static std::string choice;
	bool clicked;
public:
	ChoiceButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText);

	void checkIfPressed(graphics::MouseState& mouse) override;

	bool isClicked() const;

	static const std::string& getChoice();
	void setClicked(bool value);
};