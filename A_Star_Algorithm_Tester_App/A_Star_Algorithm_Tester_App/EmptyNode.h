#pragma once
#include "Node.h"

class EmptyNode : public Node
{
public:
	EmptyNode(float x, float y, float width, float height);

	const std::string getType() const override;
};