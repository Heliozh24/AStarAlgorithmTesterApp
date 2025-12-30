#include "PathStep.h"
#include "GraphicElement.h"
#include <sgg/graphics.h>
#include "AStarAction.h"

int PathStep::pathNumber = 0;
PathStep::PathStep(float x, float y, float width, float height): AStarAction(x,y,width,height,0.25)
{
	instancePathNumber = ++pathNumber;
	title = new Title(x - 0.2f, y, 0.12f, "Step "+ std::to_string(instancePathNumber), 0,0,0);
	setOutlineColor(16, 86, 31);
	setFillColor(16, 86, 31);
}

void PathStep::draw() const
{
	float globalTime = graphics::getGlobalTime() / 1000;
	if (globalTime >= creationTime) // draw the pathStep(node which is part of the final path from start to end node)
	{	// we draw it if and only if 0.25 seconds pass
		graphics::drawRect(getPosX(), getPosY(), getWidth(), getHeight(), getBrush());
		title->draw();
	}
}

void PathStep::resetPathNumber()
{
	pathNumber = 0;
}

PathStep::~PathStep()
{
	delete title;
}





