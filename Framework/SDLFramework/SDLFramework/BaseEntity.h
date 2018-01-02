#pragma once

class SparseGraph;

class BaseEntity
{
public:
	BaseEntity(int pNodeIndex, SparseGraph* pGraph) : nodeIndex(pNodeIndex), graph(pGraph) {}
	virtual ~BaseEntity(){}
	
	virtual void update() = 0;
	virtual void draw() = 0;

	SparseGraph* getGraph() const
	{
		return graph;
	}

	int getNodeIndex() const
	{
		return nodeIndex;
	}

	void setNodeIndex(int index)
	{
		nodeIndex = index;
	}

private:
	SparseGraph* graph;
	int nodeIndex;
};


