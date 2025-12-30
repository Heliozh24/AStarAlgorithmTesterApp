#include "AStarAction.h"
#include "GraphicElement.h"

int AStarAction::staticNumber = 0;
float AStarAction::staticTime = 0;
AStarAction::AStarAction(float x, float y, float width, float height, float timeToElapse): GraphicElement(x,y)
{
	this->width = width;
	this->height = height;
	this->timeToElapse = timeToElapse;
	instanceNumber = ++staticNumber;
	if (instanceNumber == 1)
	{
		creationTime = graphics::getGlobalTime() / 1000; // saving only the 1st's instance number
		staticTime = creationTime;
	}
	else
	{
		creationTime = staticTime + timeToElapse; // for the next instances, their time is the same as the 1st one + timeToElapse
		staticTime = creationTime;	// we do that to ensure proper delay for proper animation
	}
}
const float AStarAction::getWidth() const
{
	return width;
}

const float AStarAction::getHeight() const
{
	return height;
}

void AStarAction::resetStaticNumber() 
{
	staticNumber = 0;
}

void AStarAction::resetStaticTime()
{
	staticTime = 0;
}

AStarAction::~AStarAction()
{

}
