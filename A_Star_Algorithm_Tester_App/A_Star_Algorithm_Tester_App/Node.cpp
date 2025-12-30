#include "Node.h"
#include "GraphicElement.h"
#include <sgg/graphics.h>
#include "ObstacleNode.h"
#include "GlobalState.h"
#include "EmptyNode.h"
#include "Button.h"
#include "StartNode.h"
#include "EndNode.h"
#include <string>
#include "GridAction.h"
#include "ChoiceButton.h"
#include "NodeManager.h"
Node::Node(float x, float y, float width, float height): GraphicElement(x,y)
{
	this->width = width;
	this->height = height;
	setOutlineWidth(4.0f);
	hCost = 0;
	gCost = INT_MAX;
	parent = nullptr;
}

void Node::draw() const
{
	
	graphics::drawRect(getPosX(), getPosY(), getWidth(), getHeight(),getBrush());
}

void Node::setParent(Node* newParent)
{
	parent = newParent;
}

Node* Node::getParent() const
{
	return parent;
}

void Node::checkIfPressed(graphics::MouseState& mouse)
{
	float mouseX = graphics::windowToCanvasX(mouse.cur_pos_x);
	float mouseY = graphics::windowToCanvasY(mouse.cur_pos_y);
	if (getPosX() - getWidth() / 2 <= mouseX && mouseX <= getPosX() + getWidth() / 2 && getPosY() - getHeight() / 2 <= mouseY && mouseY <= getPosY() + getHeight() / 2)
	{
		std::pair<float, float> nodePosPair = *getPosPair();
		float width = getWidth();
		float height = getHeight();
		int pos = GlobalState::getInstance()->getNodeMap()->at(*getPosPair());
		std::string nodeTypeToBringBack = GlobalState::getInstance()->getNodeVector()->at(pos)->getType();
		if (mouse.button_left_pressed && ChoiceButton::getChoice() != " ") // if our choice is not " " we insert our node and of course delete the one that is there
		{
			NodeManager::deleteNode(*getPosPair());
			if (ChoiceButton::getChoice() == "Obstacle Node")
			{
				NodeManager::insertNode<ObstacleNode>(nodePosPair,0.4f,0.6f);
				GlobalState::getInstance()->getStackGridAction()->push(GridAction(std::pair<float, float>(nodePosPair.first, nodePosPair.second), nodeTypeToBringBack));
			}
			else if (ChoiceButton::getChoice() == "Start Node")
			{
				GlobalState::getInstance()->getStackGridAction()->push(GridAction(std::pair<float, float>(nodePosPair.first, nodePosPair.second), nodeTypeToBringBack, StartNode::getLastStartNodePositions(), "Start Node"));
				NodeManager::insertStartOrEndNode<StartNode>(nodePosPair, 0.4f, 0.6f);
			}
			else
			{
				GlobalState::getInstance()->getStackGridAction()->push(GridAction(std::pair<float, float>(nodePosPair.first, nodePosPair.second), nodeTypeToBringBack, EndNode::getLastEndNodePositions(), "End Node"));
				NodeManager::insertStartOrEndNode<EndNode>(nodePosPair, 0.4f, 0.6f);
			}
		}
		else if (mouse.button_right_pressed && !mouse.button_left_pressed)
		{
			NodeManager::deleteNode(*getPosPair());
			NodeManager::insertNode<EmptyNode>(nodePosPair, 0.4f, 0.6f);
			GlobalState::getInstance()->getStackGridAction()->push(GridAction(std::pair<float, float>(nodePosPair.first, nodePosPair.second), nodeTypeToBringBack));
		}
	}
}

const float Node::getWidth() const
{
	return width;
}

const float Node::getHeight() const
{
	return height;
}

int Node::getFCost() const
{
	return gCost+hCost;
}

int Node::getGCost() const
{
	return gCost;
}

int Node::getHCost() const
{
	return hCost;
}

void Node::setGCost(int x)
{
	gCost = x;
}

void Node::setHCost(int x)
{
	hCost = x;
}

const std::string Node::getType() const
{
	return "";

}
