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

	float getTimeAlive()
	{
		return timeAlive;
	}

	void tagNeighborBunnies(std::vector<Bunny*>& entities);

	void draw() override;
	void update() override;

private:
	SteeringBehaviors* steering;

	float timeAlive = 0.f;
};

