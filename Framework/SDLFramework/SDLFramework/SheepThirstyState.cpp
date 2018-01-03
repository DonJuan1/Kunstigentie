#include "SheepThirstyState.h"
#include "SheepWanderState.h"
#include "SparseGraph.h"
#include "Graph_SearchAStar.h"
#include "RandomGenerator.h"

SheepThirstyState* SheepThirstyState::instance()
{
	static SheepThirstyState instance;
	return &instance;
};

void SheepThirstyState::enter(Sheep * sheep)
{
	float missesJansenAverageWaterGiven = sheep->getGraph()->getMissesJansen()->getWaterGivenAverage();
	float misterJansenAverageWaterGiven = sheep->getGraph()->getMisterJansen()->getWaterGivenAverage();

	int randomPercentage = RandomGenerator::getInstance().generate(1, 100);

	if (missesJansenAverageWaterGiven > 0 && misterJansenAverageWaterGiven > 0)
	{
		float totalAverageWaterGiven = missesJansenAverageWaterGiven + misterJansenAverageWaterGiven;
		float missesJansenPercentage = missesJansenAverageWaterGiven / totalAverageWaterGiven * 100.f;
		float misterJansenPercentage = misterJansenAverageWaterGiven / totalAverageWaterGiven * 100.f;

		sheep->getGraph()->getMissesJansen()->setPercentage(missesJansenPercentage);
		sheep->getGraph()->getMisterJansen()->setPercentage(misterJansenPercentage);

		if (randomPercentage < missesJansenPercentage)
		{
			choosenJansen = sheep->getGraph()->getMissesJansen();
			
		}
		else
		{
			choosenJansen = sheep->getGraph()->getMisterJansen();
			
		}

	}
	else
	{
		if (randomPercentage > 50)
		{
			choosenJansen = sheep->getGraph()->getMissesJansen();
		}
		else
		{
			choosenJansen = sheep->getGraph()->getMisterJansen();
		}
	}
}

void SheepThirstyState::execute(Sheep * sheep)
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	if (time >= 250)
	{
		auto graph = sheep->getGraph();
		Graph_SearchAStar astar = Graph_SearchAStar(*graph, sheep->getNodeIndex(), choosenJansen->getNodeIndex());

		if (astar.GetPathToTarget().empty())
		{
			sheep->setThirst(sheep->getThirst() - static_cast<int>(choosenJansen->giveWater()));
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
