#pragma once

#include <string>

#include "State.h"
#include "MissesJansen.h"
#include "RandomGenerator.h"
#include "FWApplication.h"

class MissesJansenWanderState : public State<MissesJansen>
{
public:
	static MissesJansenWanderState* instance();

	void enter(MissesJansen*) override;
	void execute(MissesJansen*) override;
	void exit(MissesJansen*) override;

	std::string name() override;

private:
	MissesJansenWanderState()
	{};

	MissesJansenWanderState(const MissesJansenWanderState&) = delete;
	MissesJansenWanderState& operator=(const MissesJansenWanderState &) = delete;

	float time = 0;
};


