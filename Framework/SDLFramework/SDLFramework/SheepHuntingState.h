#pragma once

#include <string>

#include "State.h"
#include "Sheep.h"

class SheepHuntingState : public State<Sheep>
{
public:
	static SheepHuntingState* instance();

	void enter(Sheep*) override;
	void execute(Sheep*) override;
	void exit(Sheep*) override;

	std::string name() override;

private:
	SheepHuntingState()
	{};

	SheepHuntingState(const SheepHuntingState&) = delete;
	SheepHuntingState& operator=(const SheepHuntingState &) = delete;

	float time = 0;
};


