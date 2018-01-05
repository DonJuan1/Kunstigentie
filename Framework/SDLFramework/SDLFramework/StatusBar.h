#pragma once

#include "MissesJansen.h"
#include "MisterJansen.h"
#include "SparseGraph.h"
#include "Sheep.h"
#include "FWApplication.h"

class StatusBar
{
public:
	StatusBar(int pXPos, int pYPos, int pWidth, int pHeight, Color pBackgroundColor, SparseGraph* pGraph) : xPos(pXPos), yPos(pYPos), width(pWidth), height(pHeight), backgroundColor(pBackgroundColor), graph(pGraph) {};

	void draw();

private:
	SparseGraph* graph = nullptr;

	int xPos;
	int yPos;
	int width;
	int height;
	Color backgroundColor;
};

void StatusBar::draw()
{
	auto application = FWApplication::GetInstance();
	application->SetColor(backgroundColor);
	application->DrawRect(xPos, yPos, width, height, true);

	application->SetColor(Color(0, 0, 0, 0));

	if (graph->getSheep())
	{
		application->DrawTextt("Sheep", xPos + 4, yPos + 4);
		application->DrawTextt("Sheep State: ", xPos + 4, yPos + 20);
		application->DrawTextt(graph->getSheep()->getFSM()->CurrentState()->name(), xPos + 122, yPos + 20);

		application->DrawTextt("Sheep thirst level: ", xPos + 4, yPos + 36);
		application->DrawTextt(std::to_string(graph->getSheep()->getThirst()), xPos + 122, yPos + 36);

		application->DrawTextt("Sheep drinks level: ", xPos + 4, yPos + 52);
		application->DrawTextt(std::to_string(graph->getSheep()->getDrinks()), xPos + 122, yPos + 52);
	}

	if (graph->getMissesJansen())
	{
		application->DrawTextt("Misses Jansen State: ", xPos + 4, yPos + 164);
		application->DrawTextt(graph->getMissesJansen()->getFSM()->CurrentState()->name(), xPos + 122, yPos + 164);
		application->DrawTextt("Misses Jansen average water given: ", xPos + 4, yPos + 180);
		application->DrawTextt(std::to_string(graph->getMissesJansen()->getWaterGivenAverage()), xPos + 208, yPos + 180);
		application->DrawTextt("Misses Jansen percentage to be choosen: ", xPos + 4, yPos + 196);
		application->DrawTextt(std::to_string(graph->getMissesJansen()->getPercentage()).append("%"), xPos + 238, yPos + 196);

	}

	if (graph->getMisterJansen())
	{
		application->DrawTextt("Mister Jansen State: ", xPos + 4, yPos + 228);
		application->DrawTextt(graph->getMisterJansen()->getFSM()->CurrentState()->name(), xPos + 122, yPos + 228);
		application->DrawTextt("Mister Jansen average water given: ", xPos + 4, yPos + 244);
		application->DrawTextt(std::to_string(graph->getMisterJansen()->getWaterGivenAverage()), xPos + 208, yPos + 244);
		application->DrawTextt("Mister Jansen percentage to be choosen: ", xPos + 4, yPos + 260);
		application->DrawTextt(std::to_string(graph->getMisterJansen()->getPercentage()).append("%"), xPos + 238, yPos + 260);
	}

	if (graph->getBunnyPopulation())
	{
		int counter = 0;
		application->DrawTextt("Generation | Total bunny's alive", xPos + 4, yPos + 292);

		for (auto& gd : graph->getBunnyPopulation()->getGenerationDetails())
		{
			application->DrawTextt(std::to_string(gd.generationNumber), xPos + 4, yPos + 308 + 16 * counter);
			application->DrawTextt(std::to_string(gd.totalAlive), xPos + 82, yPos + 308 + 16 * counter);
			counter++;
		}
	}
}
