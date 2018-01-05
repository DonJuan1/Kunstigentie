#include "SheepHuntingState.h"
#include "SheepWanderState.h"
#include "SparseGraph.h"
#include "Bunny.h"
#include "Graph_SearchAStar.h"
#include <limits>

SheepHuntingState* SheepHuntingState::instance()
{
	static SheepHuntingState instance;
	return &instance;
};

void SheepHuntingState::enter(Sheep *)
{
	time = 0;
}

void SheepHuntingState::execute(Sheep * sheep)
{
	Bunny* closestBunny = nullptr;
	float closestDistance = std::numeric_limits<float>::infinity();
	Vector2D sheepPosition = sheep->getGraph()->GetNode(sheep->getNodeIndex()).Pos();

	for (auto& bunny : sheep->getGraph()->getBunnyPopulation()->getBunnies())
	{
		if (bunny->getAlive())
		{
			double distancesq = sheepPosition.DistanceSq(bunny->getPosition());
			if (distancesq < closestDistance)
			{
				closestBunny = bunny;
				closestDistance = distancesq;
			}
		}
	}

	time += FWApplication::GetInstance()->GetDeltaTime();

	if (time >= 250)
	{
		if (closestBunny != nullptr && closestDistance < 50 * 50)
		{
			int bunnyXPosition = static_cast<int>(closestBunny->getPosition().x);
			int bunnyYPosition = static_cast<int>(closestBunny->getPosition().y);
			Vector2D bunnyNodePosition = Vector2D(bunnyXPosition - bunnyXPosition % 20, bunnyYPosition - bunnyYPosition % 20);

			GraphNode* node = sheep->getGraph()->getNodesAtPosition(bunnyNodePosition);

			if (node != nullptr)
			{
				Graph_SearchAStar astar = Graph_SearchAStar(*sheep->getGraph(), sheep->getNodeIndex(), node->Index());

				if (astar.GetPathToTarget().empty())
				{
					sheep->getGraph()->resetNodes();
					sheep->getFSM()->SetCurrentState(SheepWanderState::instance());
				}
				else
				{
					sheep->getGraph()->resetNodes();
					auto path = astar.GetPathToTarget();
					sheep->setNodeIndex(path.front());
				}
			}
		}
		else
		{
			sheep->getGraph()->resetNodes();
			sheep->getFSM()->SetCurrentState(SheepWanderState::instance());
		}

		time = 0;
	}
}

void SheepHuntingState::exit(Sheep *)
{

}

std::string SheepHuntingState::name()
{
	return "Sheep hunting state";
}
