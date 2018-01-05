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
	for (int i = 0; i < 40; i++)
	{
		while (node == nullptr || !node->IsWalkable())
		{
			int randomIndex = RandomGenerator::getInstance().generateInt(0, graph->NumNodes() - 1);
			node = &graph->GetNode(randomIndex);
		}

		Bunny* bunny = new Bunny(graph);
		bunny->setPosition(node->Pos());
		generateNew(*bunny);
		bunnies.push_back(bunny);

		node = nullptr;
	}
}

void BunnyPopulation::generateNew(Bunny & bunny)
{
	bunny.setAttractionToWater(RandomGenerator::getInstance().generateFloat(-1, 1));
	bunny.setAttractionToSheep(RandomGenerator::getInstance().generateFloat(-1, 1));
	bunny.setSeparation(RandomGenerator::getInstance().generateFloat(0, 1));
	bunny.setAlignment(RandomGenerator::getInstance().generateFloat(0, 1));
	bunny.setCohesion(RandomGenerator::getInstance().generateFloat(0, 1));
}

void BunnyPopulation::createOffspring(Bunny & bunny1, Bunny & bunny2)
{
	Bunny* bunny = new Bunny(graph);
	crossOver(*bunny, bunny1, bunny2);
	mutate(*bunny);
	bunnies.push_back(bunny);
}

void BunnyPopulation::crossOver(Bunny& newBunny, Bunny& bunny1, Bunny & bunny2)
{
	float bunny1Chromosomes[] = {bunny1.getAttractionToSheep(), bunny1.getAttractionToWater(), bunny1.getSeparation(), bunny1.getAlignment(), bunny1.getCohesion()};
	float bunny2Chromosomes[] = {bunny2.getAttractionToSheep(), bunny2.getAttractionToWater(), bunny2.getSeparation(), bunny2.getAlignment(), bunny2.getCohesion()};
	std::vector<float> newChromosomes;

	int splittingpoint = RandomGenerator::getInstance().generateInt(1, 4);


	for (int i = 0; i < 5; i++)
	{
		if (i >= splittingpoint)
		{
			newChromosomes.push_back(bunny1Chromosomes[i]);
		}
		else
		{
			newChromosomes.push_back(bunny1Chromosomes[i]);
		}
	}

	newBunny.setAttractionToSheep(newChromosomes[0]);
	newBunny.setAttractionToWater(newChromosomes[1]);
	newBunny.setSeparation(newChromosomes[2]);
	newBunny.setAlignment(newChromosomes[3]);
	newBunny.setCohesion(newChromosomes[4]);
}

void BunnyPopulation::mutate(Bunny& bunny)
{
	int mutateChange = RandomGenerator::getInstance().generateInt(1, 100);
	if (mutateChange <= 10)
	{
		int mutateChromosome = RandomGenerator::getInstance().generateInt(0, 4);
		switch (mutateChromosome)
		{
			case 0: bunny.setAttractionToWater(RandomGenerator::getInstance().generateFloat(-1, 1)); break;
			case 1: bunny.setAttractionToSheep(RandomGenerator::getInstance().generateFloat(-1, 1)); break;
			case 2: bunny.setSeparation(RandomGenerator::getInstance().generateFloat(0, 1)); break;
			case 3: bunny.setAlignment(RandomGenerator::getInstance().generateFloat(0, 1)); break;
			case 4: bunny.setCohesion(RandomGenerator::getInstance().generateFloat(0, 1)); break;
		}
	}
}

void BunnyPopulation::update()
{
	for (auto& bunny : bunnies)
	{
		if(bunny->getAlive())
			bunny->update();
	}
}

void BunnyPopulation::draw()
{
	for (auto& bunny : bunnies)
	{
		if (bunny->getAlive())
			bunny->draw();
	}
}
