
#include <utility>
#include <sgg/graphics.h>
#include "GlobalState.h"

GraphicElement::GraphicElement(float x, float y)
{
	positions = new std::pair<float, float>(x, y);
}

const std::pair<float, float>* GraphicElement::getPosPair() const
{
	return positions;
}
const float GraphicElement::getPosX() const
{
	return positions->first;
}

const float GraphicElement::getPosY() const
{
	return positions->second;
}

void GraphicElement::setPosX(float x)
{
	positions->first = x;
}

void GraphicElement::setPosY(float y)
{
	positions->second = y;
}

void GraphicElement::setFillColor(float r, float g, float b)
{
	brush.fill_color[0] = r / 255.f;  // divide by 255.f because rgb values in sgg have max value of 1.f
	brush.fill_color[1] = g / 255.f; // this way we can work with 0-255 system
	brush.fill_color[2] = b / 255.f;
}

void GraphicElement::setOutlineColor(float r, float g, float b)
{
	brush.outline_color[0] = r / 255.f;
	brush.outline_color[1] = g / 255.f;
	brush.outline_color[2] = b / 255.f;
}

void GraphicElement::setOutlineWidth(float value)
{
	brush.outline_width = value;
}

const graphics::Brush& GraphicElement::getBrush() const
{
	return brush;
}

GraphicElement::~GraphicElement()
{
	delete positions;
}