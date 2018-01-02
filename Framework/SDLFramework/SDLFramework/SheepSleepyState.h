#pragma once

#include <string>

#include "State.h"
#include "Sheep.h"

class SheepSleepyState : public State<Sheep>
{
public:
	static SheepSleepyState* instance();

	void enter(Sheep*) override;
	void execute(Sheep*) override;
	void exit(Sheep*) override;

	std::string name() override;

private:
	SheepSleepyState()
	{};

	SheepSleepyState(const SheepSleepyState&) = delete;
	SheepSleepyState& operator=(const SheepSleepyState &) = delete;

	float time = 0;
};


