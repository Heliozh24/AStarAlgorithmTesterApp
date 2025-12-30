#include "EndNode.h"
#include "Node.h"
#include "EmptyNode.h"
#include "GlobalState.h"
#include "NodeManager.h"

std::pair<float, float> EndNode::lastEndNodePositions(-1,-1);
EndNode::EndNode(float x, float y, float width, float height, bool canChangeLastPos) : Node(x, y, width, height)
{
	setOutlineColor(173, 216, 230);
	setFillColor(173, 216, 230); // works just like any other node, only difference is when we move the node somewhere else,
	if (lastEndNodePositions.first == -1 && lastEndNodePositions.second == -1 && canChangeLastPos) // it deletes its "old" version
	{// no end node in the grid, no need to delete old version
		lastEndNodePositions.first = getPosX();
		lastEndNodePositions.second = getPosY();
	}
	else if (lastEndNodePositions.first != -1 && lastEndNodePositions.second != -1)
	{ // end node already on grid, remove the old one first and insert the new one
		std::pair<float, float>  lastPosPair = getLastEndNodePositions();
		NodeManager::deleteNode(lastPosPair);
		NodeManager::insertNode<EmptyNode>(lastPosPair,0.4f,0.6f);
		if (canChangeLastPos)
		{ // only 1 out of the 3 replicas of the start node can change the static last pos
			lastEndNodePositions.first = getPosX();
			lastEndNodePositions.second = getPosY();
		}
	}
}

std::pair<float, float>& EndNode::getLastEndNodePositions()
{
	return lastEndNodePositions;
}

const std::string EndNode::getType() const
{
	return "End Node";
}

EndNode::~EndNode()
{
	lastEndNodePositions.first = -1;
	lastEndNodePositions.second = -1;
}
