#pragma once
#include "Node.h"
#include <utility>
class StartNode : public Node
{
private:
	static std::pair<float, float> lastStartNodePositions;
public:

	StartNode(float x, float y, float width, float height, bool canChangeLastPos);

	static std::pair<float, float>& getLastStartNodePositions();

	const std::string getType() const override;

	~StartNode();
};