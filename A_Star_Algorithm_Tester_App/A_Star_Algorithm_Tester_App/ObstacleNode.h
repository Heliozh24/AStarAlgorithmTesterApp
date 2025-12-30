#pragma once

#include "Node.h"

class ObstacleNode : public Node
{
public:
	ObstacleNode(float x, float y, float width, float height);

	const std::string getType() const override;

};