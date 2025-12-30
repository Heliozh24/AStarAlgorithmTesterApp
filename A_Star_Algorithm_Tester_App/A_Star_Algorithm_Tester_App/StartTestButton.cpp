#include "StartTestButton.h"
#include "Button.h"
#include "GlobalState.h"
#include <vector>
#include <utility>
#include <iostream>
#include "AStarAlgorithm.h"
#include "GridUtils.h"
#include "AStarAction.h"
StartTestButton::StartTestButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText) : Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{

}

void StartTestButton::checkIfPressed(graphics::MouseState& mouse)
{
	Button::checkIfPressed(mouse);
	if (mouseHovers(mouse) && mouse.button_left_pressed)
	{
		std::pair<float, float> startNodePair(-1, -1);
		std::pair<float, float> endNodePair(-1, -1);
		for (AStarAction* aStarAction : *(GlobalState::getInstance()->getAStarActionVector()))
		{
			delete aStarAction; // in case user presses again start test without pressing end test, delete the old steps	
		}
		for (Node* node : *(GlobalState::getInstance()->getNodeVector()))
		{
			if (node->getType() == "Start Node")
			{
				startNodePair = *(node->getPosPair());
			}
			if (node->getType() == "End Node")
			{
				endNodePair = *(node->getPosPair());
			}
		}
		GlobalState::getInstance()->getAStarActionVector()->clear();
		PathStep::resetPathNumber();
		AStarAction::resetStaticNumber();
		AStarAction::resetStaticTime();
		if (startNodePair.first == -1 && startNodePair.second == -1 || endNodePair.first == -1 && endNodePair.second == -1)
		{
			std::cout << "Cannot start Test, missing Start node or End node" << std::endl;
			return;
		}
		else
		{
			AStarAlgorithm::startAlgorithm(std::pair<int, int>(GridUtils::toGx(startNodePair.first), GridUtils::toGy(startNodePair.second)), std::pair<int, int>(GridUtils::toGx(endNodePair.first), GridUtils::toGy(endNodePair.second)));
		}
	}
}
