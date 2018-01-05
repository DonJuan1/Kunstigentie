#include "MissesJansenGlobalState.h"
#include "MissesJansenWanderState.h"
#include "MissesJansenFrozenState.h"
#include "SparseGraph.h"

MissesJansenGlobalState* MissesJansenGlobalState::instance()
{
	static MissesJansenGlobalState instance;
	return &instance;
}

void MissesJansenGlobalState::enter(MissesJansen *)
{

}

void MissesJansenGlobalState::execute(MissesJansen * missesJansen)
{
	for (auto& bunny : missesJansen->getGraph()->getBunnyPopulation()->getBunnies())
	{
		if (bunny->getAlive())
		{

			double distancesq = missesJansen->getGraph()->GetNode(missesJansen->getNodeIndex()).Pos().DistanceSq(bunny->getPosition());
			if (distancesq <= 30*30)
			{
				missesJansen->getFSM()->SetCurrentState(MissesJansenFrozenState::instance());
				return;
			}
		}
	}

	missesJansen->getFSM()->SetCurrentState(MissesJansenWanderState::instance());
}

void MissesJansenGlobalState::exit(MissesJansen *)
{}

std::string MissesJansenGlobalState::name()
{
	return "Misses Jansen global state";
}
