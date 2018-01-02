#pragma once

#include "BaseEntity.h"
#include "GraphNode.h"
#include "StateMachine.h"
#include "FWApplication.h"

class SparseGraph;

class MissesJansen : public BaseEntity
{
public:
	MissesJansen(int nodeIndex, SparseGraph* graph);
	~MissesJansen();

	StateMachine<MissesJansen>* getFSM() const;

	void update() override;
	void draw() override;

private:
	StateMachine<MissesJansen>* stateMachine;
};

