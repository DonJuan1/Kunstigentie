#pragma once

#include <string>

#include "State.h"
#include "Sheep.h"

class SheepThirstyState : public State<Sheep>
{
public:
	static SheepThirstyState* instance();

	void enter(Sheep*) override;
	void execute(Sheep*) override;
	void exit(Sheep*) override;

	std::string name() override;

private:
	SheepThirstyState()
	{};

	SheepThirstyState(const SheepThirstyState&) = delete;
	SheepThirstyState& operator=(const SheepThirstyState &) = delete;

	float time = 0;
};


