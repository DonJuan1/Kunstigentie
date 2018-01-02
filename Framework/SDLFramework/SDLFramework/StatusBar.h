#pragma once
#include "MissesJansen.h"
#include "Sheep.h"
#include "FWApplication.h"

class StatusBar
{
public:
	StatusBar(int pXPos, int pYPos, int pWidth, int pHeight, Color pBackgroundColor) : xPos(pXPos), yPos(pYPos), width(pWidth), height(pHeight), backgroundColor(pBackgroundColor) {};

	void setMissesJansen(MissesJansen*);
	void setSheep(Sheep*);
	void draw();

private:
	MissesJansen* missesJansen = nullptr;
	Sheep* sheep = nullptr;

	int xPos;
	int yPos;
	int width;
	int height;
	Color backgroundColor;
};

inline void StatusBar::setMissesJansen(MissesJansen* pMissesJansen)
{
	missesJansen = pMissesJansen;
}

inline void StatusBar::setSheep(Sheep* pSheep)
{
	sheep = pSheep;
}

void StatusBar::draw()
{
	auto application = FWApplication::GetInstance();
	application->SetColor(backgroundColor);
	application->DrawRect(xPos, yPos, width, height, true);

	application->SetColor(Color(0, 0, 0, 0));

	if (sheep)
	{
		application->DrawText("Sheep", xPos + 4, yPos + 4);
		application->DrawText("Sheep State: ", xPos + 4, yPos + 20);
		application->DrawText(sheep->getFSM()->CurrentState()->name(), xPos + 122, yPos + 20);

		application->DrawText("Sheep thirst level: ", xPos + 4, yPos + 36);
		application->DrawText(std::to_string(sheep->getThirst()), xPos + 122, yPos + 36);

		application->DrawText("Sheep drinks level: ", xPos + 4, yPos + 52);
		application->DrawText(std::to_string(sheep->getDrinks()), xPos + 122, yPos + 52);
	}

	if (missesJansen)
	{
		application->DrawText("Misses Jansen State: ", xPos + 4, yPos + 164);
		application->DrawText(missesJansen->getFSM()->CurrentState()->name(), xPos + 122, yPos + 164);
	}

	
	
}