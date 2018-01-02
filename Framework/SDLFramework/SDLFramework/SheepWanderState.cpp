#include "SheepWanderState.h"
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
	if (time > 250)
	{
		auto edges = sheep->getGraph()->GetEdgesByNode(sheep->getNodeIndex());
		auto edge = edges[RandomGenerator::getInstance().generate(0, edges.size() - 1)];
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
