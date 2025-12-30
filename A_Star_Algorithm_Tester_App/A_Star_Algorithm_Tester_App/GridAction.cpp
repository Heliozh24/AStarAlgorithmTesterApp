#include "GridAction.h"
#include <string>
#include <utility>

GridAction::GridAction( const std::pair<float, float>& nodePos, const std::string& nodeTypeToBringBack, const std::pair<float, float>& secondNodePos, const std::string& secondNodeTypeToBringBack)
{
	this->nodePos = nodePos;
	this->nodeTypeToBringBack = nodeTypeToBringBack;
	this->secondNodePos = secondNodePos;
	this->secondNodeTypeToBringBack = secondNodeTypeToBringBack;
}

const std::string& GridAction::getNodeTypeToBringBack() const
{
	return nodeTypeToBringBack;
}

const std::string& GridAction::getSecondNodeTypeToBringBack() const
{
	return secondNodeTypeToBringBack;
}

const std::pair<float, float>& GridAction::getNodePos() const
{
	return nodePos;
}

const std::pair<float, float>& GridAction::getSecondNodePos() const
{
	return secondNodePos;
}
