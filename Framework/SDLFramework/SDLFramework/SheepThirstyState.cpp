#include "SheepThirstyState.h"
#include "SheepWanderState.h"
#include "SparseGraph.h"
#include "Graph_SearchAStar.h"

SheepThirstyState* SheepThirstyState::instance()
{
	static SheepThirstyState instance;
	return &instance;
};

void SheepThirstyState::enter(Sheep *)
{
	
}

void SheepThirstyState::execute(Sheep * sheep)
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	if (time >= 250)
	{
		auto graph = sheep->getGraph();
		Graph_SearchAStar astar = Graph_SearchAStar(*graph, sheep->getNodeIndex(), graph->getMissesJansen()->getNodeIndex());

		if (astar.GetPathToTarget().empty())
		{
			sheep->setThirst(0);
			sheep->setDrinks(sheep->getDrinks() + 1);
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

void SheepThirstyState::exit(Sheep *)
{

}

std::string SheepThirstyState::name()
{
	return "Sheep thirsty state";
}
