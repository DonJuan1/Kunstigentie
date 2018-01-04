#pragma once

#include "GraphNode.h"
#include "GraphEdge.h"
#include "FWApplication.h"
#include "BunnyPopulation.h"
#include "MissesJansen.h"
#include "MisterJansen.h"
#include "Sheep.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class SparseGraph
{
private:
	std::vector<GraphNode> nodes;
	std::vector<std::vector<GraphEdge>> edges;
	
	bool digraph;
	int nextNodeIndex;

	BunnyPopulation* bunnyPopulation;
	MisterJansen* misterJansen;
	MissesJansen* missesJansen;
	Sheep* sheep;
	  
public:
	SparseGraph(bool pDigraph);
	~SparseGraph();
	
	const GraphNode& GetNode(int idx) const;
	GraphNode& GetNode(int idx);

	const GraphEdge& GetEdge(int from, int to) const;
	GraphEdge& GetEdge(int from, int to);

	std::vector<GraphEdge>& GetEdgesByNode(int idx);
	
	GraphNode* getNodesAtPosition(Vector2D position)
	{
		for (auto& node : nodes)
		{
			if (node.Pos() == position)
			{
				return &node;
			}
		}

		return nullptr;
	}

	std::vector<GraphNode>& getNodes()
	{
		return nodes;
	}

	const std::vector<GraphNode>& getNodes() const
	{
		return nodes;
	}

	const std::vector<std::vector<GraphEdge>>& getEdges() const
	{
		return edges;
	}

	int GetNextFreeNodeIndex() const { return nextNodeIndex; }
	
	int AddNode(GraphNode node);

	void AddEdge(GraphEdge edge);

	int NumNodes()const
	{
		return nodes.size();
	}

	int NumActiveNodes()const
	{
		int count = 0;

		for (unsigned int n = 0; n< nodes.size(); ++n) if (nodes[n].Index() != -1) ++count;

		return count;
	}

	int NumEdges()const
	{
		int tot = 0;

		for (auto& curEdge : edges)
		{
			tot += curEdge.size();
		}

		return tot;
	}

	bool isNodePresent(int nd) const;

	bool isEdgePresent(int from, int to)const;

	bool Load(const char* FileName);
	bool Load(std::ifstream& stream);

	BunnyPopulation* getBunnyPopulation()
	{
		return bunnyPopulation;
	}

	MisterJansen* getMisterJansen()
	{
		return misterJansen;
	}

	MissesJansen* getMissesJansen()
	{
		return missesJansen;
	}

	Sheep* getSheep()
	{
		return sheep;
	}

	void draw();
	void update();
};

