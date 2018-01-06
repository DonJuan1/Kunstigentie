#include "Graph_SearchAStar.h"
#include <map>
#include <queue>
#include <functional>

void Graph_SearchAStar::Search()
{
	std::vector<int> indexes;

	indexes.push_back(m_iSource);

	while (!indexes.empty())
	{
		int NextClosestNode = indexes[0];
		for (auto& index : indexes)
		{
			if (m_FCosts[index] <= m_FCosts[NextClosestNode])
			{
				NextClosestNode = index;
			}
		}

		auto it = std::find(indexes.begin(), indexes.end(), NextClosestNode);
		indexes.erase(it);

		m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];

		searchedNodes.push_back(NextClosestNode);

		if (NextClosestNode == m_iTarget) break;

		for (auto& pE : graph.GetEdgesByNode(NextClosestNode))
		{
			double HCost = Heuristic_Euclid::Calculate(graph, m_iTarget, pE.To());
			double GCost = m_GCosts[NextClosestNode] + pE.Cost();

			if (m_SearchFrontier[pE.To()] == nullptr)
			{
				m_FCosts[pE.To()] = GCost + HCost;
				m_GCosts[pE.To()] = GCost;
				indexes.push_back(pE.To());
				m_SearchFrontier[pE.To()] = &pE;
			}
			else if (GCost < m_GCosts[pE.To()])
			{
				m_FCosts[pE.To()] = GCost + HCost;
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