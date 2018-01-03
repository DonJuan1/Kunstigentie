#include "MisterJansenWanderState.h"
#include "MisterJansenTakePhotoState.h"
#include "SparseGraph.h"

MisterJansenWanderState* MisterJansenWanderState::instance()
{
	static MisterJansenWanderState instance;
	return &instance;
}

void MisterJansenWanderState::enter(MisterJansen *)
{
	time = 0;
	wanderTime = 0;
}

void MisterJansenWanderState::execute(MisterJansen * misterJansen)
{
	time += FWApplication::GetInstance()->GetDeltaTime();
	wanderTime += FWApplication::GetInstance()->GetDeltaTime();

	if (wanderTime > 20000)
	{
		misterJansen->getFSM()->ChangeState(MisterJansenTakePhotoState::instance());
	}

	if (time > 500)
	{
		auto edges = misterJansen->getGraph()->GetEdgesByNode(misterJansen->getNodeIndex());
		auto edge = edges[RandomGenerator::getInstance().generate(0, edges.size() - 1)];
		misterJansen->setNodeIndex(edge.To());

		time = 0;
	}


}

void MisterJansenWanderState::exit(MisterJansen *)
{}

std::string MisterJansenWanderState::name()
{
	return "Mister Jansen wander state";
}
