#include "SaveFileButton.h"
#include "Button.h"
#include "GlobalState.h"
#include "FileManager.h"
#include <string>
SaveFileButton::SaveFileButton(float x, float y, float width, float height, float* defColors, float* clColors, float* titleColors, float titleSize, const std::string& titleText) : Button(x, y, width, height, defColors, clColors, titleColors, titleSize, titleText)
{

}

void SaveFileButton::checkIfPressed(graphics::MouseState& mouse)
{
	Button::checkIfPressed(mouse);
	if (mouseHovers(mouse) && mouse.button_left_pressed)
	{
		FileManager::saveFile();
	}
}