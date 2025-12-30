#pragma once
#include <vector>
#include "Node.h"
#include "Pressable.h"
#include <sgg/graphics.h>
#include <string>
#include <unordered_map>
#include "PairHashing.h"
#include <stack>
#include "PathStep.h"
#include "AStarAction.h"
#include "GridAction.h"
class GlobalState
{
private:
	int windowWidth;
	int windowHeight;
	float canvasWidth;
	float canvasHeight;
	std::vector<Node*>* nodeVector;
	std::vector<GraphicElement*>* gfxElementVector;
	std::vector<Pressable*>* pressableVector; 
	std::vector<AStarAction*>* aStarActionVector;
	static GlobalState* globalStateInstance;
	graphics::Brush backgroundBrush;
	std::unordered_map<std::pair<float, float>, int, PairHashing>* nodeMap;
	std::unordered_map<std::pair<float, float>, int, PairHashing>* pressableMap;
	std::unordered_map<std::pair<float, float>, int, PairHashing>* gfxMap;
	std::unordered_map<std::pair<int, int>, int, PairHashing>* aStarMap;
	std::unordered_map<std::pair<int, int>, int, PairHashing>* fileManagerNodeMap;
	std::unordered_map<std::pair<int, int>, int, PairHashing>* fileManagerGfxMap;
	std::unordered_map<std::pair<int, int>, int, PairHashing>* fileManagerPressableMap;
	std::stack<GridAction>* stackGridAction;
	void putTitle(float x, float y, float size, const std::string& titleText,float r, float g, float b);
	template <typename T>
	void putButton(float defR, float defG, float defB, float clR, float clG, float clB, float titleR, float titleG, float titleB, float x, float y, float width, float height, float titleSize, const std::string& titleText)
	{
		float buttonDefaultColors[] = { defR,defG,defB};
		float buttonClickedColors[] = { clR,clG,clB};
		float buttonTitleColors[] = { titleR,titleG,titleB};
		gfxElementVector->push_back(new T(x, y, width, height, buttonDefaultColors, buttonClickedColors, buttonTitleColors, titleSize,titleText));
		pressableVector->push_back(new T(x, y, width, height, buttonDefaultColors, buttonClickedColors, buttonTitleColors,titleSize,titleText));
		(*gfxMap)[std::pair<float, float>(x, y)] = gfxElementVector->size() - 1;
		(*pressableMap)[std::pair<float, float>(x, y)] = pressableVector->size() - 1;
	}
	void adjustButtonTitle(std::pair<float, float> posPair, float dx);

public:

	void draw();

	void init(int windowWidth, int windowHeight, float canvasWidth, float canvasHeight);

	void update(float dt);
	
	std::vector<Node*>* getNodeVector() const;

	std::vector<Pressable*>* getPressableVector() const;

	std::vector<AStarAction*>* getAStarActionVector() const;

	std::vector<GraphicElement*>* getGfxElementVector() const;

	int getWindowWidth() const;

	int getWindowHeight() const;

	float const getCanvasWidth() const;

	float const getCanvasHeight() const;

	std::unordered_map<std::pair<float, float>, int, PairHashing>* getNodeMap() const;

	std::unordered_map<std::pair<float, float>, int, PairHashing>* getPressableMap() const;

	std::unordered_map<std::pair<float, float>, int, PairHashing>* getGfxMap() const;

	std::unordered_map<std::pair<int, int>, int, PairHashing>* getAStarMap() const;

	std::unordered_map<std::pair<int, int>, int, PairHashing>* getFileManagerNodeMap() const;

	std::unordered_map<std::pair<int, int>, int, PairHashing>* getFileManagerGfxMap() const;

	std::unordered_map<std::pair<int, int>, int, PairHashing>* getFileManagerPressableMap() const;

	std::stack<GridAction>* getStackGridAction() const;

	void setBackground(const std::string& img);

	graphics::Brush& getBackgroundBrush();

	static GlobalState* getInstance();
	~GlobalState();
};