#include "SheepGlobalState.h"
#include "SheepSleepyState.h"
#include "SheepThirstyState.h"
#include "FWApplication.h"

SheepGlobalState* SheepGlobalState::instance()
{
	static SheepGlobalState instance;
	return &instance;
}

void SheepGlobalState::enter(Sheep* sheep) {}

void SheepGlobalState::execute(Sheep* sheep) 
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	if (sheep->getDrinks() >= 2)
	{
		sheep->getFSM()->ChangeState(SheepSleepyState::instance());
		return;
	}

	if (sheep->getThirst() >= 10)
	{
		sheep->getFSM()->ChangeState(SheepThirstyState::instance());
	}
	else
	{
		if (time >= 1000)
		{
			sheep->setThirst(sheep->getThirst() + 1);
			time = 0;
		}
	}
}

void SheepGlobalState::exit(Sheep* sheep) {}

std::string SheepGlobalState::name()
{
	return "Sheep global state";
}
