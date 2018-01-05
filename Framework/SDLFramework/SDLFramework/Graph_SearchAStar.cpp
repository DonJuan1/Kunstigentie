#include "Graph_SearchAStar.h"
#include <map>
#include <queue>
#include <functional>

void Graph_SearchAStar::Search()
{
	std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> pq;

	pq.push(std::pair<float, int>(0,m_iSource));


	while (!pq.empty())
	{
		int NextClosestNode = pq.top().second;
		pq.pop();

		m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];

		searchedNodes.push_back(NextClosestNode);

		if (NextClosestNode == m_iTarget) break;

		for (auto& pE : graph.GetEdgesByNode(NextClosestNode))
		{
			double HCost = Heuristic_Euclid::Calculate(graph, m_iTarget, pE.To());
			double GCost = m_GCosts[NextClosestNode] + pE.Cost();

			if (m_SearchFrontier[pE.To()] == nullptr)
			{
				m_GCosts[pE.To()] = GCost;
				pq.push(std::pair<float, int>(GCost + HCost, pE.To()));
				m_SearchFrontier[pE.To()] = &pE;
			}
			else if (GCost < m_GCosts[pE.To()])
			{
				m_GCosts[pE.To()] = GCost;
				m_SearchFrontier[pE.To()] = &pE;				
			}
		}
	}
}

std::list<int> Graph_SearchAStar::GetPathToTarget()const
{
	std::list<int> path;

	if (m_iTarget < 0)  return path;
	if (m_iSource == m_iTarget)  return path;

	int nd = m_iTarget;

	path.push_front(nd);

	while ((m_ShortestPathTree[nd] != 0))
	{
		nd = m_ShortestPathTree[nd]->From();
		if (nd == m_iSource)
		{
			break;
		}

		path.push_front(nd);
	}

	for (auto& nodeIndex : path)
	{
		graph.GetNode(nodeIndex).SetIsOnShortestPath(true);
	}


	for (auto& nodeIndex : searchedNodes)
	{
		graph.GetNode(nodeIndex).SetIsSearched(true);
	}

	return path;
}