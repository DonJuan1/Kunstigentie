#pragma once

#include <vector>
#include <list>
#include <cassert>

#include "SparseGraph.h"
#include "Heuristic_Euclid.h"
#include "GraphEdge.h"
#include "Heuristic_Euclid.h"

class Graph_SearchAStar
{
private:
	SparseGraph& graph;

	std::vector<double> m_GCosts;
	std::vector<double> m_FCosts;
	std::vector<const GraphEdge*> m_ShortestPathTree;
	std::vector<const GraphEdge*> m_SearchFrontier;
	int m_iSource;
	int m_iTarget;

	void Search();
public:
	std::vector<int> searchedNodes;

	Graph_SearchAStar(SparseGraph& pGraph, int source, int target) :graph(pGraph),
		m_ShortestPathTree(graph.NumNodes()),
		m_SearchFrontier(graph.NumNodes()),
		m_GCosts(graph.NumNodes(), 0.0),
		m_FCosts(graph.NumNodes(), 0.0),
		m_iSource(source),
		m_iTarget(target)
	{
		Search();
	}

	std::vector<const GraphEdge*> GetSPT() const
	{
		return m_ShortestPathTree;
	}
	
	std::list<int> GetPathToTarget() const;

	double GetCostToTarget()const
	{
		return m_GCosts[m_iTarget];
	}
};
