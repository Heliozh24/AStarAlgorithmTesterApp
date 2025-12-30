#include "NeighbourNodeCheck.h"
#include "sgg/graphics.h"

NeighbourNodeCheck::NeighbourNodeCheck(float x, float y, float width, float height, int gCost, int hCost, int fCost): AStarAction(x, y, width, height, 0.25)
{
	gCostTitle = new Title(x -0.2f, y-0.20f, 0.09f, "gCost: " + std::to_string(gCost), 255,255, 255);
	hCostTitle = new Title(x - 0.2f, y+0.15f, 0.09f, "hCost: " + std::to_string(hCost), 255, 255, 255);
	fCostTitle = new Title(x - 0.2f, y + 0.25f, 0.09f, "fCost: " + std::to_string(fCost), 255, 255, 255);
	setOutlineColor(128, 128, 128);
	setFillColor(128,128,128);
	this->posX = x;
	this->posY = y;
}

NeighbourNodeCheck::~NeighbourNodeCheck()
{
	delete gCostTitle;
	delete hCostTitle;
	delete fCostTitle;
}

void NeighbourNodeCheck::draw() const
{
	float globalTime = graphics::getGlobalTime() / 1000;
	if (globalTime >= creationTime)
	{
		graphics::drawRect(getPosX(), getPosY(), getWidth(), getHeight(), getBrush());
		gCostTitle->draw();
		hCostTitle->draw();
		fCostTitle->draw();
	}
}

void NeighbourNodeCheck::changeTitle(int gCost, int hCost, int fCost)
{
	delete gCostTitle;
	delete hCostTitle;
	delete fCostTitle;
	gCostTitle = new Title(posX - 0.2f, posY - 0.20f, 0.09f, "gCost: " + std::to_string(gCost), 255, 255, 255);
	hCostTitle = new Title(posX - 0.2f, posY + 0.15f, 0.09f, "hCost: " + std::to_string(hCost), 255, 255, 255);
	fCostTitle = new Title(posX - 0.2f, posY + 0.25f, 0.09f, "fCost: " + std::to_string(fCost), 255, 255, 255);
}
