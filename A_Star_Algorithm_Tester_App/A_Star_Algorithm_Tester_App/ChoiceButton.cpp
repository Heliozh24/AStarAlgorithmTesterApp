#include "ChoiceButton.h"
#include "Button.h"
#include <string>
#include "GlobalState.h"

float ChoiceButton::activeChoiceButtonX = -1;
float ChoiceButton::activeChoiceButtonY = -1;
std::string ChoiceButton::choice = " ";
ChoiceButton::ChoiceButton(float x, float y,  float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize,const std::string& titleText) :Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{
	clicked = false;
}

void ChoiceButton::setClicked(bool value)
{
	clicked = value;
}

const std::string& ChoiceButton::getChoice()
{
	return choice;
}

void ChoiceButton::checkIfPressed(graphics::MouseState& mouse)
{
	if (mouseHovers(mouse))
	{
		if (mouse.button_left_pressed && !clicked)
		{
			clicked = true;
			if (activeChoiceButtonX != -1 && activeChoiceButtonY != -1)
			{ // radio button logic, only 1 button can be active at the time, the active button turns off and the current one activates
				int pos1 = GlobalState::getInstance()->getGfxMap()->at(std::pair<float, float>(activeChoiceButtonX, activeChoiceButtonY));
				ChoiceButton* buttonGfx = (ChoiceButton*)(GlobalState::getInstance()->getGfxElementVector()->at(pos1));
				buttonGfx->setFillColor(buttonGfx->getDefaultColors()[0], buttonGfx->getDefaultColors()[1], buttonGfx->getDefaultColors()[2]);
				buttonGfx->setOutlineColor(buttonGfx->getDefaultColors()[0], buttonGfx->getDefaultColors()[1], buttonGfx->getDefaultColors()[2]);
				buttonGfx->setClicked(!buttonGfx->clicked); // changes colors and turns off the previous active button, same thing is being done for its replica on the pressable vector
				int pos2 = GlobalState::getInstance()->getPressableMap()->at(std::pair<float, float>(activeChoiceButtonX, activeChoiceButtonY));
				ChoiceButton* buttonPressable = (ChoiceButton*)(GlobalState::getInstance()->getPressableVector()->at(pos2));
				buttonPressable->setFillColor(buttonPressable->getDefaultColors()[0], buttonPressable->getDefaultColors()[1], buttonPressable->getDefaultColors()[2]);
				buttonPressable->setOutlineColor(buttonPressable->getDefaultColors()[0], buttonPressable->getDefaultColors()[1], buttonPressable->getDefaultColors()[2]);
				buttonPressable->setClicked(!buttonPressable->clicked);

			}

			if (getTitle()->getString() == "Start Node")
			{
				choice = "Start Node";
			}
			else if (getTitle()->getString() == "End Node")
			{
				choice = "End Node";
			}
			else
			{
				choice = "Obstacle Node";
			}
			setFillColor(getClickedColors()[0], getClickedColors()[1], getClickedColors()[2]);
			setOutlineColor(getClickedColors()[0], getClickedColors()[1], getClickedColors()[2]);
			int pos = GlobalState::getInstance()->getGfxMap()->at(*getPosPair()); // color changing logic for the current button that we press
			GlobalState::getInstance()->getGfxElementVector()->at(pos)->setFillColor(getClickedColors()[0], getClickedColors()[1], getClickedColors()[2]);
			GlobalState::getInstance()->getGfxElementVector()->at(pos)->setOutlineColor(getClickedColors()[0], getClickedColors()[1], getClickedColors()[2]);
			activeChoiceButtonX = getPosX();
			activeChoiceButtonY = getPosY();
		}
		else if (mouse.button_left_pressed && clicked)
		{
			clicked = false; // if we "deactivate" the current button, we are in state where no button is activated
			choice = " ";
			activeChoiceButtonX = -1; 
			activeChoiceButtonY = -1;
			setFillColor(getDefaultColors()[0], getDefaultColors()[1], getDefaultColors()[2]);
			setOutlineColor(getDefaultColors()[0], getDefaultColors()[1], getDefaultColors()[2]);
			int pos = GlobalState::getInstance()->getGfxMap()->at(*getPosPair()); // color changing logic
			GlobalState::getInstance()->getGfxElementVector()->at(pos)->setFillColor(getDefaultColors()[0], getDefaultColors()[1], getDefaultColors()[2]);
			GlobalState::getInstance()->getGfxElementVector()->at(pos)->setOutlineColor(getDefaultColors()[0], getDefaultColors()[1], getDefaultColors()[2]);
		}
	}
}

bool ChoiceButton::isClicked() const
{
	return clicked;
}
