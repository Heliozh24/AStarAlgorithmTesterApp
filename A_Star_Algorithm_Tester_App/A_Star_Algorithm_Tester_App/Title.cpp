#include "Title.h"
#include <sgg/graphics.h>
#include "GraphicElement.h"
Title::Title(float x,float y,float size, const const std::string& string, float r, float g,float b): GraphicElement(x,y)
{
	this->size = size;
	this->string = string;
	setFillColor(r,g,b);
}

void Title::draw() const
{
	graphics::setFont("assets\\OpenSans-ExtraBold.ttf"); // font of titles
	graphics::drawText(getPosX(),getPosY(),size,string,getBrush());
}

const std::string& Title::getString() const
{
	return string;
}

const float Title::getSize() const
{
	return size;
}