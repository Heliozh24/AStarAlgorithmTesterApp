#include "ClearGridButton.h"
#include "Button.h"
#include "GlobalState.h"
#include "EmptyNode.h"
#include "NodeManager.h"
#include <utility>
ClearGridButton::ClearGridButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText) :Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{

}

void ClearGridButton::checkIfPressed(graphics::MouseState& mouse)
{
	Button::checkIfPressed(mouse);
	if (mouseHovers(mouse) && mouse.button_left_pressed)
	{
		for (Node* node : *(GlobalState::getInstance()->getNodeVector()))
		{
			std::pair<float, float> nodePosPair = *(node->getPosPair());
			NodeManager::deleteNode(nodePosPair); // to clear grid we delete current nodes and replace them with empty nodes
			NodeManager::insertNode<EmptyNode>(nodePosPair,0.4f,0.6f);
		}
		while (!GlobalState::getInstance()->getStackGridAction()->empty()) // empties also the stack
		{
			GlobalState::getInstance()->getStackGridAction()->pop();
		}
	}
}

