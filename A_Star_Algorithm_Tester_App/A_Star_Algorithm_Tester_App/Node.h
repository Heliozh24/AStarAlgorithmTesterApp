#pragma once
#include "GraphicElement.h"
#include "Pressable.h"
#include <string>
#include <utility>

class Node: public GraphicElement, public Pressable
{
protected:
	float width, height;
	int gCost, hCost;
	Node* parent;
public:
	Node(float x, float y, float width, float height);
	void draw() const override;

	virtual void checkIfPressed(graphics::MouseState& mouse) override;

	const float getWidth() const;

	const float getHeight() const;

	virtual const std::string getType() const;

	int getFCost() const;

	int getGCost() const;

	int getHCost() const;

	void setGCost(int x);

	void setHCost(int x);

	Node* getParent() const;

	void setParent(Node* newParent);

};


