#include "SheepSleepyState.h"
#include "SheepWanderState.h"
#include "SparseGraph.h"
#include "Graph_SearchAStar.h"

SheepSleepyState* SheepSleepyState::instance()
{
	static SheepSleepyState instance;
	return &instance;
};

void SheepSleepyState::enter(Sheep *)
{
	
}

void SheepSleepyState::execute(Sheep * sheep)
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	if (time >= 250)
	{
		auto graph = sheep->getGraph();
		Graph_SearchAStar astar = Graph_SearchAStar(*graph, sheep->getNodeIndex(), sheep->getCaveIndex());

		if (astar.GetPathToTarget().empty())
		{
			sheep->setThirst(0);
			sheep->setDrinks(0);
			sheep->getFSM()->ChangeState(SheepWanderState::instance());
		}
		else
		{
			auto path = astar.GetPathToTarget();
			sheep->setNodeIndex(path.front());
		}

		time = 0;
	}
}

void SheepSleepyState::exit(Sheep *)
{

}

std::string SheepSleepyState::name()
{
	return "Sheep sleepy state";
}
