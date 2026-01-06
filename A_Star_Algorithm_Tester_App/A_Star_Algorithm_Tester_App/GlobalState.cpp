#include "GlobalState.h"
#include "Node.h"
#include "EmptyNode.h"
#include "GraphicElement.h"
#include "Pressable.h"
#include "Title.h"
#include <string>
#include "PairHashing.h"
#include <unordered_map>
#include <utility>
#include "ChoiceButton.h"
#include <stack>
#include "AStarAlgorithm.h"
#include "StartTestButton.h"
#include "EndTestButton.h"
#include "AStarAction.h"
#include "SaveFileButton.h"
#include "LoadFileButton.h"
#include "ClearGridButton.h"
#include "UndoButton.h"
void GlobalState::update(float dt) // we call polymorphically checkIfPressed which essentially checks for any updates
{
	for (Pressable* pressable : *pressableVector)
	{
		graphics::MouseState mouse;
		graphics::getMouseState(mouse);
		pressable->checkIfPressed(mouse);
	}
}

void GlobalState::setBackground( const std::string& img) // setting background
{
	backgroundBrush.texture = img;
	graphics::drawRect(canvasWidth / 2.0f, canvasHeight / 2.0f, canvasWidth, canvasHeight, backgroundBrush);
}

GlobalState* GlobalState::globalStateInstance = nullptr; // only 1 instance can exist of GlobalState

GlobalState* GlobalState::getInstance()
{
	if (globalStateInstance == nullptr)
		globalStateInstance = new GlobalState();
	return globalStateInstance;
}

void GlobalState::putTitle(float x, float y, float size, const std::string& titleText, float r, float g, float b)
{
	gfxElementVector->push_back(new Title(x, y,size,titleText,r,g,b)); // just inserts a title
	(*gfxMap)[std::pair<float, float>(x, y)] = gfxElementVector->size() - 1;
}

void GlobalState::adjustButtonTitle(std::pair<float, float> posPair, float dx) // adjusts a title
{
	int posGfxVector = gfxMap->at(posPair);
	int posPressableVector = pressableMap->at(posPair);
	Button* button1 = static_cast<Button*>(gfxElementVector->at(posGfxVector));
	button1->moveTitle(dx);
	Button* button2 = static_cast<Button*>(pressableVector->at(posPressableVector));
	button2->moveTitle(dx);
}

void GlobalState::draw() // polymorphic way to draw everything in the screen
{
	setBackground("assets\\background.png");
	for (GraphicElement* gfxElem : *gfxElementVector)
	{
		gfxElem->draw();
	}
	for (AStarAction* aStarAction : *aStarActionVector) 
	{
		aStarAction->draw();
	}
}

void GlobalState::init(int winX, int winY, float canW, float canH) // initialises all the components of the application
{
	windowWidth = winX;
	windowHeight = winY;
	canvasWidth = canW;
	canvasHeight = canH;
	nodeVector = new std::vector<Node*>();
	gfxElementVector = new std::vector<GraphicElement*>();
	pressableVector = new std::vector<Pressable*>();
	gfxMap = new std::unordered_map<std::pair<float, float>, int, PairHashing>();
	nodeMap = new std::unordered_map<std::pair<float, float>, int, PairHashing>();
	pressableMap = new std::unordered_map<std::pair<float, float>, int, PairHashing>();
	aStarMap = new std::unordered_map<std::pair<int, int>, int, PairHashing>();
	fileManagerNodeMap = new std::unordered_map<std::pair<int, int>, int, PairHashing>();
	fileManagerGfxMap = new std::unordered_map<std::pair<int, int>, int, PairHashing>();
	fileManagerPressableMap = new std::unordered_map<std::pair<int, int>, int, PairHashing>();
	aStarActionVector = new std::vector<AStarAction*>();
	stackGridAction = new std::stack<GridAction>();

	int gx = 1;
	for (float x = 0.4f; x < 5.f; x+=0.4f, gx++)
	{
		int gy = 0;
		for (float y = 2.0f; y <=5.f; y += 0.6f,gy++) // prepares all the vectors and maps
		{
			nodeVector->push_back(new EmptyNode(x, y, 0.4, 0.6));
			gfxElementVector->push_back(new EmptyNode(x,y, 0.4, 0.6));
			pressableVector->push_back(new EmptyNode(x, y, 0.4, 0.6));
			std::pair<float, float> pair(x, y);
			std::pair<int, int> intPair(gx, gy);
			(*nodeMap)[pair] = nodeVector->size() - 1;
			(*gfxMap)[pair] = gfxElementVector->size() - 1;
			(*pressableMap)[pair] = pressableVector->size() - 1;
			(*aStarMap)[intPair] = nodeVector->size() - 1;
			(*fileManagerNodeMap)[intPair] = nodeVector->size() - 1;
			(*fileManagerGfxMap)[intPair] = gfxElementVector->size() - 1;
			(*fileManagerPressableMap)[intPair] = pressableVector->size() - 1;
		}
	}
	putTitle(0.3, 1, 0.3f, "| A* Star Algorithm Tester App", 47, 79, 79); // puts titles and buttons
	putTitle(5.1, 3, 0.2f, "Click Node To Insert On Grid:", 47, 79, 79);
	putTitle(5.1, 5.1, 0.2f, "Click Node Again To Deselect", 47, 79, 79);
	putButton<ChoiceButton>(255.f, 140.f, 0.f, 169.f, 169.f, 169.f, 255.f, 255.f, 255.f, 5.6f, 3.6f, 0.8f, 0.5f, 0.11f, "Start Node");
	putButton<ChoiceButton>(0.f, 0.f, 0.f, 169.f, 169.f, 169.f, 255.f, 255.f, 255.f, 7.4f, 3.6f, 1.f, 0.5f, 0.11f, "Obstacle Node");
	putButton<ChoiceButton>(173.f, 216.f, 230.f, 169.f, 169.f, 169.f, 255.f, 255.f, 255.f, 5.9f, 4.4f, 1.2f, 0.5f, 0.12f, "End Node");
	adjustButtonTitle(std::pair<float,float>(5.9f,4.4f),0.12f);
	putButton<StartTestButton>(153.f, 0.f, 0.f,255.f, 51.f, 51.f, 255.f, 255.f, 255.f, 1.f, 6.f, 1.2f, 0.7f, 0.18f, "Start Test");
	putButton<EndTestButton>(0.f, 0.f, 153.f, 102.f, 102.f, 255.f, 255.f, 255.f, 255.f, 2.5f, 6.f, 1.2f, 0.7f, 0.18f, "End Test");
	adjustButtonTitle(std::pair<float, float>(2.5f, 6.f), 0.05f);
	putButton<SaveFileButton>(255.f, 191.f, 0.f, 255.f, 234.f, 0.f, 255.f, 255.f, 255.f, 4.5f, 6.f, 2.f, 0.7f, 0.14f, "Save Current Instance");
	putButton<LoadFileButton>(80.f, 200.f, 120.f, 140.f, 230.f, 130.f, 255.f, 255.f, 255.f, 6.8f, 6.f, 2.f, 0.7f, 0.125f, "Load Last Saved Instance");
	putButton<UndoButton>(205.f, 133.f, 63.f, 216.f, 190.f, 158.f, 255.f, 255.f, 255.f, 7.2f, 4.4f, 1.2f, 0.5f, 0.11f, "Undo Last Action");
	putButton<ClearGridButton>(144.f, 110.f, 149.f, 184.f, 110.f, 209.f, 255.f, 255.f, 255.f, 6.45f, 3.6f, 0.8f, 0.5f, 0.12f, "Clear Grid");
}

GlobalState::~GlobalState()
{
	for (Node* node : *nodeVector)
	{
		delete node;
	}

	for (GraphicElement* gfxElem : *gfxElementVector)
	{
		delete gfxElem;
	}

	for (Pressable* pressable : *pressableVector)
	{
		delete pressable;
	}

	for (AStarAction* aStarAction : *aStarActionVector)
	{
		delete aStarAction;
	}

	delete nodeVector; // realease of memory that was taken for the components to use
	delete gfxElementVector;
	delete pressableVector;
	delete nodeMap;
	delete gfxMap;
	delete pressableMap;
	delete aStarActionVector;
	delete aStarMap;
	delete fileManagerNodeMap;
	delete fileManagerGfxMap;
	delete fileManagerPressableMap;
	delete stackGridAction;
}

std::vector<Node*>* GlobalState::getNodeVector() const
{
	return nodeVector;
}

std::vector<Pressable*>* GlobalState::getPressableVector() const
{
	return pressableVector;
}

std::vector<AStarAction*>* GlobalState::getAStarActionVector() const
{
	return aStarActionVector;
}

std::vector<GraphicElement*>* GlobalState::getGfxElementVector() const
{
	return gfxElementVector;
}

int GlobalState::getWindowWidth() const
{
	return windowWidth;
}

int GlobalState::getWindowHeight() const
{
	return windowHeight;
}

float const GlobalState::getCanvasWidth() const
{
	return canvasWidth;
}

float const GlobalState::getCanvasHeight() const
{
	return canvasHeight;
}

std::unordered_map<std::pair<float, float>, int, PairHashing>* GlobalState:: getNodeMap() const
{
	return nodeMap;
}

std::unordered_map<std::pair<float, float>, int, PairHashing>* GlobalState::getPressableMap() const
{
	return pressableMap;
}

std::unordered_map<std::pair<float, float>, int, PairHashing>* GlobalState::getGfxMap() const
{
	return gfxMap;
}

std::unordered_map<std::pair<int, int>, int, PairHashing>* GlobalState::getAStarMap() const
{
	return aStarMap;
}

std::unordered_map<std::pair<int, int>, int, PairHashing>* GlobalState::getFileManagerNodeMap() const
{
	return fileManagerNodeMap;
}

std::unordered_map<std::pair<int, int>, int, PairHashing>* GlobalState::getFileManagerGfxMap() const
{
	return fileManagerGfxMap;
}

std::unordered_map<std::pair<int, int>, int, PairHashing>* GlobalState::getFileManagerPressableMap() const
{
	return fileManagerPressableMap;
}

std::stack<GridAction>* GlobalState::getStackGridAction() const
{
	return stackGridAction;
}

graphics::Brush& GlobalState::getBackgroundBrush()
{
	return backgroundBrush;
}
