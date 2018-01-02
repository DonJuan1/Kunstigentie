#pragma once

#include <string>

#include "State.h"
#include "Sheep.h"

class SheepGlobalState : public State<Sheep>
{
public:
	static SheepGlobalState* instance();

	void enter(Sheep*) override;
	void execute(Sheep*) override;
	void exit(Sheep*) override;

	std::string name() override;

private:
	SheepGlobalState() {};

	SheepGlobalState(const SheepGlobalState&) = delete;
	SheepGlobalState& operator=(const SheepGlobalState &) = delete;

	float time = 0;
};

