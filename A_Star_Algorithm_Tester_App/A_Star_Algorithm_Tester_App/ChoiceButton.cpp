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
				ChoiceButton* buttonGfx = static_cast<ChoiceButton*>(GlobalState::getInstance()->getGfxElementVector()->at(pos1));
				// static_cast to ChoiceButton*, faster and we are 100% sure we are getting a choiceButton
				// because of the pos we got from the maps
				buttonGfx->setClicked(!buttonGfx->clicked); // turns off the previous active button, same thing is being done for its replica on the pressable vector
				int pos2 = GlobalState::getInstance()->getPressableMap()->at(std::pair<float, float>(activeChoiceButtonX, activeChoiceButtonY));
				ChoiceButton* buttonPressable = static_cast<ChoiceButton*>(GlobalState::getInstance()->getPressableVector()->at(pos2));
				buttonPressable->changeButtonColor(buttonPressable->getDefaultColors()); // the changeButtonColor method will also change the color of the replica on the gfx vector
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
			changeButtonColor(getClickedColors());
			activeChoiceButtonX = getPosX();
			activeChoiceButtonY = getPosY();
		}
		else if (mouse.button_left_pressed && clicked)
		{
			clicked = false; // if we "deactivate" the current button, we are in state where no button is activated
			choice = " ";
			activeChoiceButtonX = -1; 
			activeChoiceButtonY = -1;
			changeButtonColor(getDefaultColors());
		}
	}
}

bool ChoiceButton::isClicked() const
{
	return clicked;
}
