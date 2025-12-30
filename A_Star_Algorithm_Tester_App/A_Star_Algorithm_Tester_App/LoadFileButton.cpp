#include "LoadFileButton.h"
#include "GlobalState.h"
#include "FileManager.h"
LoadFileButton::LoadFileButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText) : Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{

}

void LoadFileButton::checkIfPressed(graphics::MouseState& mouse)
{
	Button::checkIfPressed(mouse);
	if (mouseHovers(mouse) && mouse.button_left_pressed)
	{
		FileManager::loadFile();
	}
}
