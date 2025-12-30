#pragma once
#include "GraphicElement.h"
#include "sgg/graphics.h"
#include <string>

class Title : public GraphicElement
{
private:
	std::string string;
	float size;
public:

	Title(float x,float y,float size, const std::string& string,float r,float g,float b);

	void draw() const override;

	const std::string& getString() const;

	const float getSize() const;
};