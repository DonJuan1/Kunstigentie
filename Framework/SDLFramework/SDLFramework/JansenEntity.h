#pragma once

#include "GraphEntity.h"
#include "GraphNode.h"
#include "StateMachine.h"
#include "FWApplication.h"

class SparseGraph;

class JansenEntity : public GraphEntity
{
protected:
	float waterGiven = 0;
	float timesWaterGiven = 0;
	float pecrentage = 50;

public:
	JansenEntity(int nodeIndex, SparseGraph* graph) : GraphEntity(nodeIndex, graph) {};

	virtual float giveWater() = 0;

	float getWaterGivenAverage()
	{
		if (timesWaterGiven > 0)
		{
			return waterGiven / timesWaterGiven;
		}
		else
		{
			return 0.f;
		}
	}

	void setPercentage(float pPercentage)
	{
		pecrentage = pPercentage;
	}

	float getPercentage()
	{
		return pecrentage;
	}

};

