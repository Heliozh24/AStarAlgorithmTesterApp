#pragma once
#include <utility>
#include "StartNode.h"
#include "EndNode.h"
#include "GlobalState.h"
class NodeManager
{
public:
	template <typename T>
	static void insertNode(const std::pair<float, float>& nodePosPair, float width, float height) // inserting node to the system
	{
		int posNodeVector = GlobalState::getInstance()->getNodeMap()->at(nodePosPair); // find 3 positions of each vector using maps
		int posGfxVector = GlobalState::getInstance()->getGfxMap()->at(nodePosPair);
		int posPressableVector = GlobalState::getInstance()->getPressableMap()->at(nodePosPair);
		GlobalState::getInstance()->getNodeVector()->at(posNodeVector) = new T(nodePosPair.first, nodePosPair.second, width, height); // create the node of type T in the positions provided by the maps
		GlobalState::getInstance()->getGfxElementVector()->at(posGfxVector) = new T(nodePosPair.first, nodePosPair.second, width, height);
		GlobalState::getInstance()->getPressableVector()->at(posPressableVector) = new T(nodePosPair.first, nodePosPair.second, width, height);
	}

	template <typename T>
	static void insertStartOrEndNode(const std::pair<float, float>& nodePosPair, float width, float height)
	{
		int posNodeVector = GlobalState::getInstance()->getNodeMap()->at(nodePosPair);
		int posGfxVector = GlobalState::getInstance()->getGfxMap()->at(nodePosPair);
		int posPressableVector = GlobalState::getInstance()->getPressableMap()->at(nodePosPair);
		GlobalState::getInstance()->getNodeVector()->at(posNodeVector) = new T(nodePosPair.first, nodePosPair.second, width, height,false);
		GlobalState::getInstance()->getGfxElementVector()->at(posGfxVector) = new T(nodePosPair.first, nodePosPair.second, width, height,false);
		GlobalState::getInstance()->getPressableVector()->at(posPressableVector) = new T(nodePosPair.first, nodePosPair.second, width, height,true);
	}

	template <typename T>
	static void fileManagerInsertNode(const std::pair<int, int>& nodePosPair, const std::pair<float, float>& realNodePosPair, float width, float height)
	{
		int posNodeVector = GlobalState::getInstance()->getFileManagerNodeMap()->at(nodePosPair); // fileManagerInsertions and deletions work the same, only difference is the maps and the pair we use (int instead of float)
		int posGfxVector = GlobalState::getInstance()->getFileManagerGfxMap()->at(nodePosPair);
		int posPressableVector = GlobalState::getInstance()->getFileManagerPressableMap()->at(nodePosPair);
		GlobalState::getInstance()->getNodeVector()->at(posNodeVector) = new T(realNodePosPair.first, realNodePosPair.second, width, height); // realNodePosePair refers to node's actual position and not the grid position (gx,gy) which is used to find its position in the vectors.
		GlobalState::getInstance()->getGfxElementVector()->at(posGfxVector) = new T(realNodePosPair.first, realNodePosPair.second, width, height);
		GlobalState::getInstance()->getPressableVector()->at(posPressableVector) = new T(realNodePosPair.first, realNodePosPair.second, width, height);
	}

	template <typename T>
	static void fileManagerInsertStartOrEndNode(const std::pair<int, int>& nodePosPair, const std::pair<float, float>& realNodePosPair, float width, float height)
	{
		int posNodeVector = GlobalState::getInstance()->getFileManagerNodeMap()->at(nodePosPair);
		int posGfxVector = GlobalState::getInstance()->getFileManagerGfxMap()->at(nodePosPair);
		int posPressableVector = GlobalState::getInstance()->getFileManagerPressableMap()->at(nodePosPair);
		GlobalState::getInstance()->getNodeVector()->at(posNodeVector) = new T(realNodePosPair.first, realNodePosPair.second, width, height, false);
		GlobalState::getInstance()->getGfxElementVector()->at(posGfxVector) = new T(realNodePosPair.first, realNodePosPair.second, width, height, false);
		GlobalState::getInstance()->getPressableVector()->at(posPressableVector) = new T(realNodePosPair.first, realNodePosPair.second, width, height, true);
	}

	static void deleteNode(const std::pair<float, float>& nodePosPair);
	static void fileManagerDeleteNode(const std::pair<int, int>& nodePosPair);
};