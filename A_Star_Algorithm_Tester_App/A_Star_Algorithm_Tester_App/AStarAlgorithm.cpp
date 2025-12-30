#include "AStarAlgorithm.h"
#include "PathStep.h"
#include "GlobalState.h"
#include "Node.h"
#include <utility>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "GridUtils.h"
#include "NeighbourNodeCheck.h"
#include "Title.h"
void AStarAlgorithm::startAlgorithm(const std::pair<int,int>& startPosPair, const std::pair<int,int>& goalPosPair)
{
	int startPos = GlobalState::getInstance()->getAStarMap()->at(startPosPair); // finding start
	int goalPos = GlobalState::getInstance()->getAStarMap()->at(goalPosPair); // and goal nodes respectively
	Node* startNode = GlobalState::getInstance()->getNodeVector()->at(startPos);
	Node* goalNode = GlobalState::getInstance()->getNodeVector()->at(goalPos);
	std::vector<Node*> openVector; // openVector, contains nodes which we havent finished analysing yet
	std::set<std::pair<int,int>> closedSet; // closedSet, contains nodes which we have done analysing
	int aStarActionArray[17]{ 0 }; // max h cost is the max length of the array, this array is used to find aStarAction objects inside aStarVector
	openVector.push_back(startNode); // start by pushing startNode in open list
	while (!openVector.empty()) // if oprn list is empty, that means we have no nodes to analyse anymore, finished
	{
		int pos = 0;
		Node* currentNode = openVector.at(0);
		for (int i = 1; i < openVector.size(); i++) // finding node with minimum f cost on open list.
		{
			if (openVector.at(i)->getFCost() < currentNode->getFCost() || openVector.at(i)->getFCost() == currentNode->getFCost() && openVector.at(i)->getHCost() < currentNode->getHCost())
			{
				currentNode = openVector.at(i);
				pos = i;
			}
		}
		openVector.erase(openVector.begin()+pos); // erase node with min f cost from open list
		closedSet.insert(std::pair<int,int>(GridUtils::toGx(currentNode->getPosX()), GridUtils::toGy(currentNode->getPosY()))); // put it on closed list, since we are done analysing it from previous iterations 
		if (currentNode == goalNode) // case where we find the goalNode
		{
			tracePath(startNode,goalNode); // finds the path that leads from start to --> end
			return;
		}
		for (Node* neighbour : getNeighbours(currentNode)) // iterating neighbours
		{
			if (neighbour->getType() == "Obstacle Node" || (closedSet.find(std::pair<int, int>(GridUtils::toGx(neighbour->getPosX()), GridUtils::toGy(neighbour->getPosY()))) != closedSet.end()))
			{
				continue; // if the neighbour is an obstacle or we have already analysed them(they are in closed list) ignore and continue
			}
			int newMovementCostToNeighbour = currentNode->getGCost() + ManhattanDistance(std::pair<int,int>(GridUtils::toGx(neighbour->getPosX()), GridUtils::toGy(neighbour->getPosY())), std::pair<int, int>(GridUtils::toGx(currentNode->getPosX()), GridUtils::toGy(currentNode->getPosY())));
			if (newMovementCostToNeighbour < neighbour->getGCost() || !vectorContains(neighbour, openVector)) // the gCost of the currentNode + the distance between the neighbour 
			{	//and the current node is equal to the total cost to move from the startNode to the specific neighbour using the currentNode
				neighbour->setGCost(newMovementCostToNeighbour); // if we havent examined at all the node or we have found a better path to move to the neighbor, update gCost
				neighbour->setHCost(ManhattanDistance(std::pair<int, int>(GridUtils::toGx(neighbour->getPosX()), GridUtils::toGy(neighbour->getPosY())), std::pair<int, int>(GridUtils::toGx(goalNode->getPosX()), GridUtils::toGy(goalNode->getPosY()))));
				neighbour->setParent(currentNode); // set hCost as distance between neighbour and goalNode and set neighbors parent as the currentNode
				if (!vectorContains(neighbour, openVector))
				{
					openVector.push_back(neighbour); // if node isnt on openlist, add them
					if (neighbour != goalNode) // create an aStarAction (animation which shows costs of neighbour)
					{
						GlobalState::getInstance()->getAStarActionVector()->push_back(new NeighbourNodeCheck(neighbour->getPosX(), neighbour->getPosY(), neighbour->getWidth(), neighbour->getHeight(), neighbour->getGCost(), neighbour->getHCost(), neighbour->getFCost()));
						aStarActionArray[neighbour->getHCost()] = GlobalState::getInstance()->getAStarActionVector()->size() - 1;
					}
				}
				else
				{
					if (neighbour != goalNode)
					{ // if we revisit the node, that means we update the costs,we found a better path towards the neighbours, update costs (title)
						NeighbourNodeCheck* neighbourNodeCheck = (NeighbourNodeCheck*) GlobalState::getInstance()->getAStarActionVector()->at(aStarActionArray[neighbour->getHCost()]);
						neighbourNodeCheck->changeTitle(neighbour->getGCost(), neighbour->getHCost(), neighbour->getFCost());
					}
				}
			}
		}
	}
	std::cout << "The Algorithm could not find a path." << std::endl; // A Star fails
}

std::vector<Node*> AStarAlgorithm::getNeighbours(const Node* currentNode) // just finds the 4 neighbours (top,down,left,right)
{
	int posNeighbour = 0;
	Node* neighbour = nullptr;
	std::vector<Node*> neighbours;
	int gx = GridUtils::toGx(currentNode->getPosX());
	int gy = GridUtils::toGy(currentNode->getPosY());
	for (int i = -1; i <= 1; i +=2)
	{
		if(isValid(gx+i,gy))
			findAndPushNeighbour(neighbours, gx + i, gy);
		if(isValid(gx,gy+i))
			findAndPushNeighbour(neighbours, gx, gy + i);
	}
	return neighbours;
}

void AStarAlgorithm::findAndPushNeighbour(std::vector<Node*>& neighbours, int x, int y)
{
	int posNeighbour = GlobalState::getInstance()->getAStarMap()->at(std::pair<int, int>(x,y));
	Node* neighbour = GlobalState::getInstance()->getNodeVector()->at(posNeighbour);
	neighbours.push_back(neighbour);
}

bool AStarAlgorithm::isValid(int x, int y)
{
	return (x >= 1) && (x <= 12) && (y >= 0) && (y <= 5); // check if node is in bounds of grid
}


void AStarAlgorithm::tracePath(const Node* startNode,const Node* goalNode)
{
	std::vector<Node*> path;
	Node* currentNode = goalNode->getParent();
	while (currentNode != startNode)
	{
		path.insert(path.begin(),currentNode);
		currentNode = currentNode->getParent();
	}
	for (Node* node : path) // follow the parents of each node to find the path
	{
		GlobalState::getInstance()->getAStarActionVector()->push_back( new PathStep(node->getPosX(),node->getPosY(),node->getWidth(),node->getHeight()));
	}
	std::cout << "Succesfully found a path." << std::endl;
}

int AStarAlgorithm::ManhattanDistance(const std::pair<int, int>& currPosPair, const std::pair<int, int>& goalPosPair)
{
	return abs(currPosPair.first - goalPosPair.first) + abs(currPosPair.second - goalPosPair.second);
	// simple way to find distances, works because we only have to find 4 neighbours, otherwise 
	// go with Euclidean distance.
}

bool AStarAlgorithm::vectorContains(const Node* nodeToFind, const std::vector<Node*>& vectorNode)
{ // checks if a node is on the open list
	int nodeGx;
	int nodeGy;
	int nodeToFindGx = GridUtils::toGx(nodeToFind->getPosX());
	int nodeToFindGy = GridUtils::toGy(nodeToFind->getPosY());
	for (Node* node : vectorNode)
	{
		nodeGx = GridUtils::toGx(node->getPosX());
		nodeGy = GridUtils::toGy(node->getPosY());
		if (std::pair<int, int>(nodeGx, nodeGy) == std::pair<int, int>(nodeToFindGx, nodeToFindGy))
		{
			return true;
		}
	}
	return false;
}
