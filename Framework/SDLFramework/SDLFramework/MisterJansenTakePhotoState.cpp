#include "MisterJansenTakePhotoState.h"
#include "MisterJansenWanderState.h"
#include "SparseGraph.h"

MisterJansenTakePhotoState* MisterJansenTakePhotoState::instance()
{
	static MisterJansenTakePhotoState instance;
	return &instance;
}

void MisterJansenTakePhotoState::enter(MisterJansen *)
{
	time = 0;
}

void MisterJansenTakePhotoState::execute(MisterJansen * misterJansen)
{
	time += FWApplication::GetInstance()->GetDeltaTime();

	if (time > 10000)
	{
		misterJansen->getFSM()->ChangeState(MisterJansenWanderState::instance());
	}
}

void MisterJansenTakePhotoState::exit(MisterJansen *)
{}

std::string MisterJansenTakePhotoState::name()
{
	return "Mister Jansen take photo state";
}
