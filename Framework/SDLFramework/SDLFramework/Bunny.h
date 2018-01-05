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

	void setAlive(bool alive)
	{
		isAlive = alive;
	}

	bool getAlive()
	{
		return isAlive;
	}

	void tagNeighborBunnies(std::vector<Bunny*>& entities);

	void draw() override;
	void update() override;

private:
	SteeringBehaviors* steering;

	bool isAlive = true;
	float timeAlive = 0.f;
};

