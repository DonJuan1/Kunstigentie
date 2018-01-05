#pragma once

#include <string>

#include "State.h"
#include "MissesJansen.h"
#include "RandomGenerator.h"
#include "FWApplication.h"

class MissesJansenFrozenState : public State<MissesJansen>
{
public:
	static MissesJansenFrozenState* instance();

	void enter(MissesJansen*) override;
	void execute(MissesJansen*) override;
	void exit(MissesJansen*) override;

	std::string name() override;

private:
	MissesJansenFrozenState()
	{};

	MissesJansenFrozenState(const MissesJansenFrozenState&) = delete;
	MissesJansenFrozenState& operator=(const MissesJansenFrozenState &) = delete;
};


