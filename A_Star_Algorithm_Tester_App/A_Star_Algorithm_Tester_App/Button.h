#pragma once

#include "GraphicElement.h"
#include "Pressable.h"
#include <string>
#include "Title.h"

class Button: public GraphicElement, public Pressable
{
protected:
	float width, height;
	float defaultColors[3];
	float clickedColors[3];
	float titleColors[3];
	Title* title;
	void changeButtonColor(const float* buttonColors);
	bool mouseHovers(graphics::MouseState& mouse) const;
public:
	Button(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText);

	virtual void checkIfPressed(graphics::MouseState& mouse);

	void draw() const override;

	const float getWidth() const;

	const float getHeight() const;

	const Title* getTitle() const;

	const float* getDefaultColors() const;

	const float* getClickedColors() const;

	const float* getTitleColors() const;

	void moveTitle(float dx);

	virtual ~Button();

};