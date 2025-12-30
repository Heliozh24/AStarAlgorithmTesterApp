#include <sgg/graphics.h>
#include "Title.h"
#include "Button.h"
#include "GraphicElement.h"
#include "GlobalState.h"

Button::Button(float x, float y, float width, float height, float* defColors, float* clColors, float* tlColors, float tlSize, const std::string& tlText) : GraphicElement(x, y)
{
	title = new Title(x-width/3,y,tlSize,tlText,tlColors[0], tlColors[1], tlColors[2]);
	this->width = width;
	this->height = height;
	this->title = title;
	for (int i = 0; i <= 2; i++)
	{
		defaultColors[i] = defColors[i];
		clickedColors[i] = clColors[i];
		titleColors[i] = tlColors[i];
	}
	setFillColor(defaultColors[0],defaultColors[1],defaultColors[2]);
	setOutlineColor(defaultColors[0], defaultColors[1], defaultColors[2]);
	setOutlineWidth(4.0f);
}

void Button::checkIfPressed(graphics::MouseState& mouse)
{
	if(mouseHovers(mouse))
	{
		if (mouse.button_left_pressed)
		{
			changeButtonColor(getClickedColors());
		}
		else if (mouse.button_left_released)
		{
			changeButtonColor(getDefaultColors());
		}
	}
	else
	{
		changeButtonColor(getDefaultColors());
	}
}


const Title* Button::getTitle() const
{
	return title;
}

const float Button::getWidth() const 
{
	return width;
}

void Button::changeButtonColor(const float* buttonColors)
{
	int pos = GlobalState::getInstance()->getGfxMap()->at(*getPosPair());
	setFillColor(buttonColors[0], buttonColors[1], buttonColors[2]); // here the color changes are being done on the current button
	setOutlineColor(buttonColors[0], buttonColors[1], buttonColors[2]); // using map, we find pos of  the replica of this button on the gfx vector to change colors
	GlobalState::getInstance()->getGfxElementVector()->at(pos)->setFillColor(buttonColors[0], buttonColors[1], buttonColors[2]);
	GlobalState::getInstance()->getGfxElementVector()->at(pos)->setOutlineColor(buttonColors[0], buttonColors[1], buttonColors[2]);
}

bool Button::mouseHovers(graphics::MouseState& mouse) const // checks if we hover the mouse cursor on top of the button
{
	float mouseX = graphics::windowToCanvasX(mouse.cur_pos_x);
	float mouseY = graphics::windowToCanvasY(mouse.cur_pos_y);
	return (getPosX() - getWidth() / 2 <= mouseX && mouseX <= getPosX() + getWidth() / 2 && getPosY() - getHeight() / 2 <= mouseY && mouseY <= getPosY() + getHeight() / 2);
}

const float Button::getHeight() const
{
	return height;
}

Button::~Button()
{
	delete title;
}

const float* Button::getDefaultColors() const
{
	return defaultColors;
}

const float* Button::getClickedColors() const
{
	return clickedColors;
}

const float* Button::getTitleColors() const
{
	return titleColors;
}

void Button::moveTitle(float dx) // relocates title horizontally by dx value in case it needs adjustment
{
	Title* temp = title;
	title = new Title(temp->getPosX()+dx, temp->getPosY(), temp->getSize(), temp->getString(),getTitleColors()[0], getTitleColors()[1], getTitleColors()[2]);
	delete temp;
}

void Button::draw() const // simply draws the button
{
	graphics::drawRect(getPosX(),getPosY(),getWidth(),getHeight(),getBrush());
	title->draw();
}