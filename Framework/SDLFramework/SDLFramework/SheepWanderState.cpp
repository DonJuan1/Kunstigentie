#include "SheepWanderState.h"
#include "SheepHuntingState.h"
#include "SparseGraph.h"

SheepWanderState* SheepWanderState::instance()
{
	static SheepWanderState instance;
	return &instance;
};

void SheepWanderState::enter(Sheep* sheep)
{
	float time = 0;
}

void SheepWanderState::execute(Sheep* sheep)
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	for (auto& bunny : sheep->getGraph()->getBunnyPopulation()->getBunnies())
	{
		if (bunny->getAlive())
		{
			double distancesq = sheep->getGraph()->GetNode(sheep->getNodeIndex()).Pos().DistanceSq(bunny->getPosition());
			if (distancesq <= 50 * 50)
			{
				sheep->getFSM()->SetCurrentState(SheepHuntingState::instance());
				return;
			}
		}
	}

	if (time > 250)
	{
		auto edges = sheep->getGraph()->GetEdgesByNode(sheep->getNodeIndex());
		auto edge = edges[RandomGenerator::getInstance().generateInt(0, edges.size() - 1)];
		sheep->setNodeIndex(edge.To());

		time = 0;
	}
}

void SheepWanderState::exit(Sheep* sheep)
{
	// Not needed
}

std::string SheepWanderState::name()
{
	return "Sheep wander state";
}
