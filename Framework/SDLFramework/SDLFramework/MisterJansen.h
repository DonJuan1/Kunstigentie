#pragma once

#include "JansenEntity.h"
#include "GraphNode.h"
#include "StateMachine.h"
#include "FWApplication.h"

class SparseGraph;

class MisterJansen : public JansenEntity
{
public:
	MisterJansen(int nodeIndex, SparseGraph* graph);
	~MisterJansen();

	StateMachine<MisterJansen>* getFSM() const;

	float giveWater() override;
	void update() override;
	void draw() override;

private:
	StateMachine<MisterJansen>* stateMachine;
};

