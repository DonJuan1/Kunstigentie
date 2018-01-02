#pragma once

#include "BaseEntity.h"
#include "StateMachine.h"
#include "FWApplication.h"

class SparseGraph;

class Sheep : public BaseEntity
{
public:
	Sheep(int nodeIndex, SparseGraph* graph);
	~Sheep();

	StateMachine<Sheep>* getFSM() const;

	void setThirst(int amount);
	int getThirst() const;
	void setDrinks(int amount);
	int getDrinks() const;
	int getCaveIndex() const;

	void update() override;
	void draw() override;

private:
	StateMachine<Sheep>* stateMachine;

	int thirst = 0;
	int drinks = 0;
	int caveIndex = -1;
};

