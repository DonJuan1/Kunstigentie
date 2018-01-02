#pragma once

#include <string>

#include "State.h"
#include "Sheep.h"
#include "RandomGenerator.h"
#include "FWApplication.h"

class SheepWanderState : public State<Sheep>
{
public:
	static SheepWanderState* instance();
	
	void enter(Sheep*) override;
	void execute(Sheep*) override;
	void exit(Sheep*) override;

	std::string name() override;

private:
	SheepWanderState() {};

	SheepWanderState(const SheepWanderState&) = delete;
	SheepWanderState& operator=(const SheepWanderState &) = delete;

	float time = 0;
};


