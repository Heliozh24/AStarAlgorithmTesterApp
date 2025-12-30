#include "StartNode.h"
#include "Node.h"
#include <sgg/graphics.h>
#include "GlobalState.h"
#include "EmptyNode.h"
#include "NodeManager.h"
std::pair<float, float> StartNode::lastStartNodePositions(-1, -1);

StartNode::StartNode(float x, float y, float width, float height, bool canChangeLastPos) : Node(x, y, width, height)
{
	setOutlineColor(255, 140, 0);
	setFillColor(255, 140, 0);
	gCost = 0; // exactly same logic as End Node, check comments of EndNode.cpp to understand logic here
	if (lastStartNodePositions.first == -1 && lastStartNodePositions.second == -1 && canChangeLastPos)
	{
		lastStartNodePositions.first = getPosX();
		lastStartNodePositions.second = getPosY();
	}
	else if (lastStartNodePositions.first != -1 && lastStartNodePositions.second != -1)
	{
		std::pair<float, float>  lastPosPair = getLastStartNodePositions();
		NodeManager::deleteNode(lastPosPair);
		NodeManager::insertNode<EmptyNode>(lastPosPair, 0.4f, 0.6f);
		if (canChangeLastPos)
		{
			lastStartNodePositions.first = getPosX();
			lastStartNodePositions.second = getPosY();
		}
	}
}

std::pair<float, float>& StartNode::getLastStartNodePositions()
{
	return lastStartNodePositions;
}

const std::string StartNode::getType() const
{
	return "Start Node";
}

StartNode::~StartNode()
{
	
	lastStartNodePositions.first = -1;
	lastStartNodePositions.second = -1;
}

