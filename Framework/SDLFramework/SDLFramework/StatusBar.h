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
		application->DrawText("Misses Jansen average water given: ", xPos + 4, yPos + 180);
		application->DrawText(std::to_string(missesJansen->getWaterGivenAverage()), xPos + 208, yPos + 180);
		application->DrawText("Misses Jansen percentage to be choosen: ", xPos + 4, yPos + 196);
		application->DrawText(std::to_string(missesJansen->getPercentage()).append("%"), xPos + 238, yPos + 196);

	}

	if (misterJansen)
	{
		application->DrawText("Mister Jansen State: ", xPos + 4, yPos + 228);
		application->DrawText(misterJansen->getFSM()->CurrentState()->name(), xPos + 122, yPos + 228);
		application->DrawText("Mister Jansen average water given: ", xPos + 4, yPos + 244);
		application->DrawText(std::to_string(misterJansen->getWaterGivenAverage()), xPos + 208, yPos + 244);
		application->DrawText("Mister Jansen percentage to be choosen: ", xPos + 4, yPos + 260);
		application->DrawText(std::to_string(misterJansen->getPercentage()).append("%"), xPos + 238, yPos + 260);
	}
}
