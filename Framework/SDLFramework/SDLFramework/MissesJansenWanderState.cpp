#include "MissesJansenWanderState.h"
#include "SparseGraph.h"

MissesJansenWanderState* MissesJansenWanderState::instance()
{
	static MissesJansenWanderState instance;
	return &instance;
}

void MissesJansenWanderState::enter(MissesJansen *)
{
	
}

void MissesJansenWanderState::execute(MissesJansen * missesJansen)
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	if (time > 500)
	{
		auto edges = missesJansen->getGraph()->GetEdgesByNode(missesJansen->getNodeIndex());
		auto edge = edges[RandomGenerator::getInstance().generate(0, edges.size() - 1)];
		missesJansen->setNodeIndex(edge.To());

		time = 0;
	}
}

void MissesJansenWanderState::exit(MissesJansen *)
{}

std::string MissesJansenWanderState::name()
{
	return "Misses Jansen wander state";
}
