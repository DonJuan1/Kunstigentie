#pragma once

#include <vector>
#include "Bunny.h"
#include "Vector2D.h"

class SparseGraph;

class BunnyPopulation
{
private:
	std::vector<Bunny*> bunnies;
	SparseGraph* graph;
	int generation = 0;
	int avarageTimeAlive = 0;

	void generateNew(Bunny& bunny);
	void createOffspring(Bunny& bunny1, Bunny& bunny2);

	void crossOver(Bunny& newBunny, Bunny& bunny1, Bunny& bunny2);
	void mutate(Bunny& bunny);

public:
	BunnyPopulation(SparseGraph*);
	~BunnyPopulation();

	std::vector<Bunny*>& getBunnies();
	void generatePopulation();

	void update();
	void draw();
};