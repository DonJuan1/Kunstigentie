#pragma once

#include <string>

#include "State.h"
#include "MissesJansen.h"
#include "RandomGenerator.h"
#include "FWApplication.h"

class MissesJansenGlobalState : public State<MissesJansen>
{
public:
	static MissesJansenGlobalState* instance();

	void enter(MissesJansen*) override;
	void execute(MissesJansen*) override;
	void exit(MissesJansen*) override;

	std::string name() override;

private:
	MissesJansenGlobalState()
	{};

	MissesJansenGlobalState(const MissesJansenGlobalState&) = delete;
	MissesJansenGlobalState& operator=(const MissesJansenGlobalState &) = delete;
};


