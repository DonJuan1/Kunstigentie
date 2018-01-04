#pragma once

#include "MissesJansen.h"
#include "MisterJansen.h"
#include "Sheep.h"
#include "FWApplication.h"

class StatusBar
{
public:
	StatusBar(int pXPos, int pYPos, int pWidth, int pHeight, Color pBackgroundColor) : xPos(pXPos), yPos(pYPos), width(pWidth), height(pHeight), backgroundColor(pBackgroundColor) {};

	void setMisterJansen(MisterJansen*);
	void setMissesJansen(MissesJansen*);
	void setSheep(Sheep*);
	void draw();

private:
	MisterJansen * misterJansen = nullptr;
	MissesJansen* missesJansen = nullptr;
	Sheep* sheep = nullptr;

	int xPos;
	int yPos;
	int width;
	int height;
	Color backgroundColor;
};

inline void StatusBar::setMisterJansen(MisterJansen* pMisterJansen)
{
	misterJansen = pMisterJansen;
}

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
		application->DrawTextt("Sheep", xPos + 4, yPos + 4);
		application->DrawTextt("Sheep State: ", xPos + 4, yPos + 20);
		application->DrawTextt(sheep->getFSM()->CurrentState()->name(), xPos + 122, yPos + 20);

		application->DrawTextt("Sheep thirst level: ", xPos + 4, yPos + 36);
		application->DrawTextt(std::to_string(sheep->getThirst()), xPos + 122, yPos + 36);

		application->DrawTextt("Sheep drinks level: ", xPos + 4, yPos + 52);
		application->DrawTextt(std::to_string(sheep->getDrinks()), xPos + 122, yPos + 52);
	}

	if (missesJansen)
	{
		application->DrawTextt("Misses Jansen State: ", xPos + 4, yPos + 164);
		application->DrawTextt(missesJansen->getFSM()->CurrentState()->name(), xPos + 122, yPos + 164);
		application->DrawTextt("Misses Jansen average water given: ", xPos + 4, yPos + 180);
		application->DrawTextt(std::to_string(missesJansen->getWaterGivenAverage()), xPos + 208, yPos + 180);
		application->DrawTextt("Misses Jansen percentage to be choosen: ", xPos + 4, yPos + 196);
		application->DrawTextt(std::to_string(missesJansen->getPercentage()).append("%"), xPos + 238, yPos + 196);

	}

	if (misterJansen)
	{
		application->DrawTextt("Mister Jansen State: ", xPos + 4, yPos + 228);
		application->DrawTextt(misterJansen->getFSM()->CurrentState()->name(), xPos + 122, yPos + 228);
		application->DrawTextt("Mister Jansen average water given: ", xPos + 4, yPos + 244);
		application->DrawTextt(std::to_string(misterJansen->getWaterGivenAverage()), xPos + 208, yPos + 244);
		application->DrawTextt("Mister Jansen percentage to be choosen: ", xPos + 4, yPos + 260);
		application->DrawTextt(std::to_string(misterJansen->getPercentage()).append("%"), xPos + 238, yPos + 260);
	}
}
