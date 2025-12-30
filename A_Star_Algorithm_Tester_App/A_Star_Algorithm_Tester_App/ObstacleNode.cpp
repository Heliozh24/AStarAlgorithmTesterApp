#include "ObstacleNode.h"
#include "Node.h"

ObstacleNode::ObstacleNode(float x, float y, float width, float height): Node(x,y,width,height)
{
	setOutlineColor(0, 0, 0);
	setFillColor(0, 0, 0);
}

const std::string ObstacleNode::getType() const
{
	return "Obstacle Node";
}
