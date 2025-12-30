#pragma once
#include "AStarAction.h"
#include "Title.h"
#include <string>
class NeighbourNodeCheck : public AStarAction
{
private:
	Title* gCostTitle;
	Title* hCostTitle;
	Title* fCostTitle;
	float posX, posY;
public:
	NeighbourNodeCheck(float x, float y, float width, float height,int gCost, int hCost, int fCost);
	~NeighbourNodeCheck();
	void draw() const override;
	void changeTitle( int gCost, int hCost, int fCost);
};