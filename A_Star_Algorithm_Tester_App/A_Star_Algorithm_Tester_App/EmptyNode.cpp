#include "EmptyNode.h"
#include "Node.h"

EmptyNode::EmptyNode(float x, float y, float width, float height): Node(x,y,width,height)
{
	setOutlineColor(0, 0, 0);
	setFillColor(255, 255, 255);
}

const std::string EmptyNode::getType() const
{
	return "Empty Node";
}
