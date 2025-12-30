#pragma once
#include "GraphicElement.h"
#include <sgg/graphics.h>
#include "Title.h"
#include "AStarAction.h"

class PathStep: public AStarAction
{
private:
	static int pathNumber;
	int instancePathNumber;
	Title* title;
public:
public:
	PathStep(float x, float y, float width, float height);

	void draw() const override;
	static void resetPathNumber();

	~PathStep();

};