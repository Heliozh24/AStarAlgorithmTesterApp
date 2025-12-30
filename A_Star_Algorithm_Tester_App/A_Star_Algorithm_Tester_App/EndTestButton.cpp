#include "EndTestButton.h"
#include "GlobalState.h"
#include <vector>
#include "AStarAlgorithm.h"
#include "AStarAction.h"

EndTestButton::EndTestButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText) : Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{

}


void EndTestButton::checkIfPressed(graphics::MouseState& mouse) //  finishes the test
{
	Button::checkIfPressed(mouse);
	if (mouseHovers(mouse) && mouse.button_left_pressed)
	{
		for (AStarAction* aStarAction : *(GlobalState::getInstance()->getAStarActionVector()))
		{
			delete aStarAction; 
		} // deletes all the aStarActions (animations)
		GlobalState::getInstance()->getAStarActionVector()->clear();
		PathStep::resetPathNumber(); // reset all data referring to aStarActions animations
		AStarAction::resetStaticNumber();
		AStarAction::resetStaticTime();
	}
}