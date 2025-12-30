#pragma once
#include "sgg/graphics.h"
#include "GraphicElement.h"
#include <string>
class AStarAction: public GraphicElement
{
protected:
	float timeToElapse,width,height,creationTime;
	static int staticNumber;
	static float staticTime;
	int instanceNumber;
public:
	AStarAction(float x, float y, float width, float height, float timeToElapse);
	void draw() const = 0;
	~AStarAction() override;
	const float getWidth() const;
	const float getHeight() const;
	static void resetStaticNumber();
	static void resetStaticTime();
};