#pragma once

#include "Vector2D.h"

class SparseGraph;

class BaseEntity
{

protected:
	SparseGraph * graph;
	Vector2D position;
	float visibilityRadius = 30;

public:
	BaseEntity(SparseGraph* pGraph) : graph(pGraph) {}
	virtual ~BaseEntity(){}
	
	virtual void update() = 0;
	virtual void draw() = 0;

	SparseGraph* getGraph() const
	{
		return graph;
	}

	void setPosition(Vector2D newPos)
	{
		position = newPos;
	}

	Vector2D getPosition() const
	{
		return position;
	}

	float getVisibilityRadius() const
	{
		return visibilityRadius;
	}
};


