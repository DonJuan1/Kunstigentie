#pragma once

#include <string>

#include "State.h"
#include "MisterJansen.h"
#include "RandomGenerator.h"
#include "FWApplication.h"

class MisterJansenTakePhotoState : public State<MisterJansen>
{
public:
	static MisterJansenTakePhotoState* instance();

	void enter(MisterJansen*) override;
	void execute(MisterJansen*) override;
	void exit(MisterJansen*) override;

	std::string name() override;

private:
	MisterJansenTakePhotoState()
	{};

	MisterJansenTakePhotoState(const MisterJansenTakePhotoState&) = delete;
	MisterJansenTakePhotoState& operator=(const MisterJansenTakePhotoState &) = delete;

	float time = 0;
};


