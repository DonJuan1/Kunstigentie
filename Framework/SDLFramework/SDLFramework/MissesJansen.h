#pragma once

#include "JansenEntity.h"
#include "GraphNode.h"
#include "StateMachine.h"
#include "FWApplication.h"

class SparseGraph;

class MissesJansen : public JansenEntity
{
public:
	MissesJansen(int nodeIndex, SparseGraph* graph);
	~MissesJansen();

	StateMachine<MissesJansen>* getFSM() const;

	float giveWater() override;
	void update() override;
	void draw() override;

private:
	StateMachine<MissesJansen>* stateMachine;
};

