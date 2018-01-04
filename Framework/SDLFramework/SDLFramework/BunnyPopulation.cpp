#include "BunnyPopulation.h"
#include "SparseGraph.h"
#include "RandomGenerator.h"
#include "GraphNode.h"

BunnyPopulation::BunnyPopulation(SparseGraph * pGraph) : graph(pGraph)
{
	
}

BunnyPopulation::~BunnyPopulation()
{
	for (auto& bunny : bunnies)
	{
		delete bunny;
	}
}

std::vector<Bunny*>& BunnyPopulation::getBunnies()
{
	return bunnies;
}

void BunnyPopulation::generatePopulation()
{
	GraphNode* node = nullptr;
	for (int i = 0; i < 20; i++)
	{
		while (node == nullptr || !node->IsWalkable())
		{
			int randomIndex = RandomGenerator::getInstance().generateInt(0, graph->NumNodes() - 1);
			node = &graph->GetNode(randomIndex);
		}

		Bunny* bunny = new Bunny(graph);
		bunny->setPosition(node->Pos());
		bunnies.push_back(bunny);

		node = nullptr;
	}
}

void BunnyPopulation::update()
{
	for (auto& bunny : bunnies)
	{
		bunny->update();
	}
}

void BunnyPopulation::draw()
{
	for (auto& bunny : bunnies)
	{
		bunny->draw();
	}
}
