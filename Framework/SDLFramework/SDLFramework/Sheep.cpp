#include "Sheep.h"
#include "SparseGraph.h"
#include "SheepWanderState.h"
#include "SheepGlobalState.h"

Sheep::Sheep(int nodeIndex, SparseGraph* graph) : BaseEntity(nodeIndex, graph)
{
	stateMachine = new StateMachine<Sheep>(this);

	stateMachine->SetGlobalState(SheepGlobalState::instance());
	stateMachine->SetCurrentState(SheepWanderState::instance());

	caveIndex = nodeIndex;
}

Sheep::~Sheep()
{
	delete stateMachine;
}

StateMachine<Sheep>* Sheep::getFSM() const
{
	return stateMachine;
}

void Sheep::setThirst(int amount)
{
	thirst = amount;
}

int Sheep::getThirst() const
{
	return thirst;
}

void Sheep::setDrinks(int amount)
{
	drinks = amount;
}

int Sheep::getDrinks() const
{
	return drinks;
}

int Sheep::getCaveIndex() const
{
	return caveIndex;
}

void Sheep::update()
{
	stateMachine->Update();
}

void Sheep::draw()
{
	auto position = getGraph()->GetNode(getNodeIndex()).Pos();
	FWApplication::GetInstance()->SetColor(Color(255, 255, 255, 255));
	FWApplication::GetInstance()->DrawRect(position.x + 5, position.y + 5, 10, 10, true);
}
