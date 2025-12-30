#pragma once
#include <string>
#include <utility>
class GridAction
{
private:
	std::string nodeTypeToBringBack,secondNodeTypeToBringBack;
	std::pair<float, float> nodePos, secondNodePos;

public:
	GridAction( const std::pair<float, float>& nodePos, const std::string& nodeTypeToBringBack, const std::pair<float, float>& secondNodePos = std::pair<float,float>(-1,-1), const std::string& secondNodeTypeToBringBack = "None");
	const std::string& getNodeTypeToBringBack() const;
	const std::string& getSecondNodeTypeToBringBack() const;
	const std::pair<float, float>& getNodePos() const;
	const std::pair<float, float>& getSecondNodePos() const;
};