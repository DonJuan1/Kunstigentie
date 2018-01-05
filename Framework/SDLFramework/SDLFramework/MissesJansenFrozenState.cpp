#include "MissesJansenFrozenState.h"
#include "SparseGraph.h"

MissesJansenFrozenState* MissesJansenFrozenState::instance()
{
	static MissesJansenFrozenState instance;
	return &instance;
}

void MissesJansenFrozenState::enter(MissesJansen *)
{

}

void MissesJansenFrozenState::execute(MissesJansen * missesJansen)
{
	
}

void MissesJansenFrozenState::exit(MissesJansen *)
{}

std::string MissesJansenFrozenState::name()
{
	return "Misses Jansen frozen state";
}
