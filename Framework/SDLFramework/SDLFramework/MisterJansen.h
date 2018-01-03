#pragma once

#include "BaseEntity.h"
#include "GraphNode.h"
#include "StateMachine.h"
#include "FWApplication.h"

class SparseGraph;

class MisterJansen : public BaseEntity
{
public:
	MisterJansen(int nodeIndex, SparseGraph* graph);
	~MisterJansen();

	StateMachine<MisterJansen>* getFSM() const;

	void update() override;
	void draw() override;

private:
	StateMachine<MisterJansen>* stateMachine;
};

