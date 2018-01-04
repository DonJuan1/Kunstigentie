#pragma once

#include <vector>

#include "MovingEntity.h"
#include "SteeringBehaviors.h"

class SparseGraph;

class Bunny : public MovingEntity
{
public:
	Bunny(SparseGraph* graph) : MovingEntity(graph)
	{
		steering = new SteeringBehaviors(this);
	}

	~Bunny()
	{
		delete steering;
	}

	void tagNeighborBunnies(std::vector<Bunny*>& entities);
	void draw() override;
	void update() override;

private:
	SteeringBehaviors* steering;
};

