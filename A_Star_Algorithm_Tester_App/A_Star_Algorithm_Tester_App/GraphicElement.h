#pragma once
#include <utility>
#include <sgg/graphics.h>

class GraphicElement
{
protected:
	std::pair<float, float>* positions;
	graphics::Brush brush;

public:
	virtual void draw() const = 0;

	GraphicElement(float x, float y);

	const std::pair<float, float>* getPosPair() const;
	const float getPosX() const;

	const float getPosY() const;

	void setPosX(float x);

	void setPosY(float y);

	void setFillColor(float r, float g, float b);

	void setOutlineColor(float r, float g, float b);

	void setOutlineWidth(float value);

	const graphics::Brush& getBrush() const;

	virtual ~GraphicElement();

};