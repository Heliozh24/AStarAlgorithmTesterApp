#include "UndoButton.h"
#include "GlobalState.h"
#include <stack>
#include "GridAction.h"
#include <string>
#include "StartNode.h"
#include "EmptyNode.h"
#include "ObstacleNode.h"
#include "EndNode.h"
#include "NodeManager.h"

UndoButton::UndoButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText) : Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{

}

void UndoButton::checkIfPressed(graphics::MouseState& mouse) // the undo functionality
{
	Button::checkIfPressed(mouse);
	if (mouseHovers(mouse) && mouse.button_left_pressed)
	{
		std::stack<GridAction>* stackGridAction = GlobalState::getInstance()->getStackGridAction();
		if (!stackGridAction->empty()) // depends on a stack
		{
			GridAction action = stackGridAction->top();
			stackGridAction->pop(); // pop the gridAction object
			const std::pair<float, float> posPair = action.getNodePos();
			const std::string& nodeTypeToBringBack = action.getNodeTypeToBringBack();
			const std::pair<float, float> secondPosPair = action.getSecondNodePos();
			const std::string& secondNodeTypeToBringBack = action.getSecondNodeTypeToBringBack();
			NodeManager::deleteNode(posPair);
			if (nodeTypeToBringBack == "Start Node") // we bring back the node which the stack tells us
			{
				NodeManager::insertStartOrEndNode<StartNode>(posPair,0.4f,0.6f);
			}
			else if (nodeTypeToBringBack == "End Node")
			{
				NodeManager::insertStartOrEndNode<EndNode>(posPair, 0.4f, 0.6f);
			}
			else if (nodeTypeToBringBack == "Obstacle Node")
			{
				NodeManager::insertNode<ObstacleNode>(posPair, 0.4f, 0.6f);
			}
			else
			{
				NodeManager::insertNode<EmptyNode>(posPair, 0.4f, 0.6f);
			}
			if (secondPosPair.first != -1 && secondPosPair.second != -1) // to be here that means, we have start or end node
			{ // and they removed an old version of theirs, so we bring that back aswell.
				NodeManager::deleteNode(secondPosPair);
				if (secondNodeTypeToBringBack == "Start Node")
				{
					NodeManager::insertStartOrEndNode<StartNode>(secondPosPair, 0.4f, 0.6f);
				}
				else
				{
					NodeManager::insertStartOrEndNode<EndNode>(secondPosPair, 0.4f, 0.6f);
				}
			}
		}
	}
}

