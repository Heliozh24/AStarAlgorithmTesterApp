#include "sgg/graphics.h"
#include "GlobalState.h"


void draw()
{

	GlobalState::getInstance()->draw();
}
void update(float dt)
{
	GlobalState::getInstance()->update(dt);
}

int main()
{
	GlobalState* globalState = GlobalState::getInstance(); // creates a GlobalState instance
	globalState->init(1500, 1000, 8.f, 8.f); // activates it
	graphics::createWindow(globalState->getWindowWidth(), globalState->getWindowHeight(), "A* Algorithm Tester App");
	graphics::setDrawFunction(draw); // set draw function
	graphics::setUpdateFunction(update); // and update function those of globalState
	graphics::setCanvasSize(globalState->getCanvasWidth(), globalState->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_STRETCH);
	graphics::startMessageLoop(); // draw and update are called all the time till we close window then we realease memory "delete globalState"
	delete globalState;
	return 0;
}

