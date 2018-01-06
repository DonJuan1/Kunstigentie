#include "MissesJansen.h"
#include "SparseGraph.h"
#include "MissesJansenWanderState.h"
#include "MissesJansenGlobalState.h"
#include "RandomGenerator.h"

MissesJansen::MissesJansen(int nodeIndex, SparseGraph* graph) : JansenEntity(nodeIndex, graph)
{
	stateMachine = new StateMachine<MissesJansen>(this);

	stateMachine->SetCurrentState(MissesJansenWanderState::instance());
	stateMachine->SetPreviousState(MissesJansenWanderState::instance());
	stateMachine->SetGlobalState(MissesJansenGlobalState::instance());
}

MissesJansen::~MissesJansen()
{
	delete stateMachine;
}

StateMachine<MissesJansen>* MissesJansen::getFSM() const
{
	return stateMachine;
}

float MissesJansen::giveWater()
{
	int waterAmount = RandomGenerator::getInstance().generateInt(10, 80);

	timesWaterGiven++;
	waterGiven += waterAmount;

	return waterAmount;
}

void MissesJansen::update()
{
	stateMachine->Update();
}

void MissesJansen::draw()
{
	auto position = getGraph()->GetNode(getNodeIndex()).Pos();
	FWApplication::GetInstance()->SetColor(Color(192, 0, 192, 255));
	FWApplication::GetInstance()->DrawRect(position.x + 5, position.y + 5, 10, 10, true);
}
