#include "MisterJansen.h"
#include "SparseGraph.h"
#include "MisterJansenWanderState.h"
#include "RandomGenerator.h"

MisterJansen::MisterJansen(int nodeIndex, SparseGraph* graph) : JansenEntity(nodeIndex, graph)
{
	stateMachine = new StateMachine<MisterJansen>(this);

	stateMachine->SetCurrentState(MisterJansenWanderState::instance());
}

MisterJansen::~MisterJansen()
{
	delete stateMachine;
}

StateMachine<MisterJansen>* MisterJansen::getFSM() const
{
	return stateMachine;
}

float MisterJansen::giveWater()
{
	float waterAmount = RandomGenerator::getInstance().generateInt(30, 50);

	timesWaterGiven++;
	waterGiven += waterAmount;

	return waterAmount;
}

void MisterJansen::update()
{
	stateMachine->Update();
}

void MisterJansen::draw()
{
	auto position = getGraph()->GetNode(getNodeIndex()).Pos();
	FWApplication::GetInstance()->SetColor(Color(192, 0, 0, 255));
	FWApplication::GetInstance()->DrawRect(position.x + 5, position.y + 5, 10, 10, true);
}
