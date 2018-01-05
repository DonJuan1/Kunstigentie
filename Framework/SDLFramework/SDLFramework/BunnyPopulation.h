#pragma once

#include <vector>
#include "Bunny.h"
#include "Vector2D.h"

class SparseGraph;

struct GenerationDetails
{
	int generationNumber = 0;
	int totalAlive = 0;
};

class BunnyPopulation
{
private:
	std::vector<Bunny*> bunnies;
	SparseGraph* graph;
	
	std::vector<GenerationDetails> generationDetails;
	
	int generation = 0;
	int avarageTimeAlive = 0;

	void generateNew(Bunny& bunny);
	void createOffspring(Bunny& bunny1, Bunny& bunny2);

	void thinningOut();
	void crossOver(Bunny& newBunny, Bunny& bunny1, Bunny& bunny2);
	void mutate(Bunny& bunny);

public:
	BunnyPopulation(SparseGraph*);
	~BunnyPopulation();

	std::vector<Bunny*>& getBunnies();
	std::vector<GenerationDetails>& getGenerationDetails();
	void generateNewPopulation();
	void generateBetterPopulation();

	void update();
	void draw();
};