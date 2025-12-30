#pragma once
#include "Node.h"
#include <utility>
#include <vector>

class AStarAlgorithm
{
private:
	static void findAndPushNeighbour(std::vector<Node*>& neighbours,int x, int y);
	static bool isValid(int x, int y);
	static std::vector<Node*> getNeighbours(const Node* currentNode);
	static void tracePath(const Node* startNode,const Node* goalNode);
	static int ManhattanDistance(const std::pair<int, int>& currPosPair, const std::pair<int, int>& goalPosPair);
	static bool vectorContains(const Node* nodeToFind, const std::vector<Node*>& vectorNode);
public:
	static void startAlgorithm(const std::pair<int, int>& startPosPair, const std::pair<int, int>& goalPosPair);
};