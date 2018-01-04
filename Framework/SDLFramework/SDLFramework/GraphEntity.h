#pragma once

#include "BaseEntity.h"

class SparseGraph;

class GraphEntity : public BaseEntity
{
public:
	GraphEntity(int pNodeIndex, SparseGraph* graph) : BaseEntity(graph), nodeIndex(pNodeIndex){};

	int getNodeIndex() const
	{
		return nodeIndex;
	}

	void setNodeIndex(int index)
	{
		nodeIndex = index;
	}

protected:
	int nodeIndex;
};

