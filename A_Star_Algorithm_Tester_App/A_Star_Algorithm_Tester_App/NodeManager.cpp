#include "NodeManager.h"
#include <utility>
#include "GlobalState.h"

void NodeManager::deleteNode(const std::pair<float, float>& nodePosPair)
{
	int posNodeVector = GlobalState::getInstance()->getNodeMap()->at(nodePosPair); // same logic as insertion
	int posGfxVector = GlobalState::getInstance()->getGfxMap()->at(nodePosPair);
	int posPressableVector = GlobalState::getInstance()->getPressableMap()->at(nodePosPair);
	delete GlobalState::getInstance()->getNodeVector()->at(posNodeVector);  // but now we delete
	delete GlobalState::getInstance()->getGfxElementVector()->at(posGfxVector);
	delete GlobalState::getInstance()->getPressableVector()->at(posPressableVector);
}

void NodeManager::fileManagerDeleteNode(const std::pair<int,int>& nodePosPair)
{
	int posNodeVector = GlobalState::getInstance()->getFileManagerNodeMap()->at(nodePosPair); // same logic as above
	int posGfxVector = GlobalState::getInstance()->getFileManagerGfxMap()->at(nodePosPair); // but with fileManagerMaps
	int posPressableVector = GlobalState::getInstance()->getFileManagerPressableMap()->at(nodePosPair);
	delete GlobalState::getInstance()->getNodeVector()->at(posNodeVector);
	delete GlobalState::getInstance()->getGfxElementVector()->at(posGfxVector);
	delete GlobalState::getInstance()->getPressableVector()->at(posPressableVector);
}
