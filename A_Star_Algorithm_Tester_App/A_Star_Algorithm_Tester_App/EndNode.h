#pragma once
#include "Node.h"
class EndNode : public Node
{
private:
	static std::pair<float, float> lastEndNodePositions;
public:

	EndNode(float x, float y, float width, float height, bool canChangeLastPos);

	static std::pair<float, float>& getLastEndNodePositions();

	const std::string getType() const override;

	~EndNode();
};