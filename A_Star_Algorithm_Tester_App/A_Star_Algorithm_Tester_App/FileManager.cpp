#include "FileManager.h"
#include "GlobalState.h"
#include <vector>
#include <iostream>
#include "Node.h"
#include <fstream>
#include <string>
#include "EmptyNode.h"
#include <sstream>
#include <utility>
#include "StartNode.h"
#include "ObstacleNode.h"
#include "EndNode.h"
#include "GridUtils.h"
#include "NodeManager.h"

void FileManager::saveFile()
{ // saves current instance
	std::vector<Node*>* vectorNode = GlobalState::getInstance()->getNodeVector();
	std::string filename = "assets\\FileManagerOutput.txt";
	std::ofstream file(filename);
	for (Node* node: *vectorNode)
	{ // sets the stucture of the txt file
		file << node->getType() + "|" << std::to_string(GridUtils::toGx(node->getPosX())) + "|" << std::to_string(GridUtils::toGy(node->getPosY())) << std::endl;
	}
	if (file.fail()) { // failed to write/save // we check if we fail because we write
		std::cerr << "Could not write data" << std::endl;
	}
	else
	{
		std:: cout << "Succesfully saved current instance." << std:: endl; // success
	}
	file.close();
}

void FileManager::loadFile() // loading instance
{
	for (Node* node : *(GlobalState::getInstance()->getNodeVector()))
	{
		std::pair<float, float> nodePosPair = *(node->getPosPair());
		NodeManager::deleteNode(nodePosPair); //  to load first, we have to delete the current grid setup
		NodeManager::insertNode<EmptyNode>(nodePosPair, 0.4f, 0.6f);
	}
	while (!GlobalState::getInstance()->getStackGridAction()->empty()) // empty the stack
	{
		GlobalState::getInstance()->getStackGridAction()->pop();
	}
	int pos;
	std::pair<float, float> realNodePosPair;
	std::pair<int, int> nodePosPair;
	int nodePosX;
	int nodePosY;
	std::string nodeType;
	std::string line;
	std::string dataReaden;
	std::string filename = "assets\\FileManagerOutput.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Unable to load file." << std::endl;
		return;
	}
	while (std::getline(file, line)) // we search each line etc. Line 1: Empty Node | x | y
	{
		std::stringstream stringStream(line); // in each line we search for its data, NodeType,posX,posY
		// to do that, we treat it as a stream of string, then we search it until we find a "|"
		std::getline(stringStream, dataReaden, '|');
		nodeType = dataReaden;

		std::getline(stringStream, dataReaden, '|');
		nodePosX = std::stoi(dataReaden);

		std::getline(stringStream, dataReaden, '|');
		nodePosY = std::stoi(dataReaden);

		nodePosPair = std::pair<int, int>(nodePosX, nodePosY);
		pos = GlobalState::getInstance()->getFileManagerNodeMap()->at(nodePosPair);
		realNodePosPair = *(GlobalState::getInstance()->getNodeVector()->at(pos)->getPosPair());
		NodeManager::fileManagerDeleteNode(std::pair<int, int>(nodePosX, nodePosY));

		if (nodeType == "Start Node") // create the data(nodes) readen from the file to the grid
		{
			NodeManager::fileManagerInsertStartOrEndNode<StartNode>(nodePosPair,realNodePosPair,0.4f,0.6f);
		}
		else if (nodeType == "End Node")
		{
			NodeManager::fileManagerInsertStartOrEndNode<EndNode>(nodePosPair, realNodePosPair, 0.4f, 0.6f);
		}
		else if (nodeType == "Obstacle Node")
		{
			NodeManager::fileManagerInsertNode<ObstacleNode>(nodePosPair, realNodePosPair, 0.4f, 0.6f);
		}
		else
		{
			NodeManager::fileManagerInsertNode<EmptyNode>(nodePosPair, realNodePosPair, 0.4f, 0.6f);
		}
	}
	if (!file.eof()) // we check if we reached end of file, because we read it
	{
		file.close(); // failed to read/load
		std::cerr << "Failed to load data correctly." << std::endl;
	}
	else
	{
		std::cout << "Succesfully loaded last saved instance." << std::endl;  // success
	}
	file.close();
}

