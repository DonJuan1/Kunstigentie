#pragma once

#include <string>

#include "State.h"
#include "MisterJansen.h"
#include "RandomGenerator.h"
#include "FWApplication.h"

class MisterJansenWanderState : public State<MisterJansen>
{
public:
	static MisterJansenWanderState* instance();

	void enter(MisterJansen*) override;
	void execute(MisterJansen*) override;
	void exit(MisterJansen*) override;

	std::string name() override;

private:
	MisterJansenWanderState()
	{};

	MisterJansenWanderState(const MisterJansenWanderState&) = delete;
	MisterJansenWanderState& operator=(const MisterJansenWanderState &) = delete;

	float time = 0;
	float wanderTime = 0;
};


