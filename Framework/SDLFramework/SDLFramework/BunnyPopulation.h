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

public:
	BunnyPopulation(SparseGraph*);
	~BunnyPopulation();

	std::vector<Bunny*>& getBunnies();
	void generatePopulation();

	void update();
	void draw();
};