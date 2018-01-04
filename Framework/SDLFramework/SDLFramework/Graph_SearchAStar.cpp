#include "Graph_SearchAStar.h"


void Graph_SearchAStar::Search()
{
	for (auto& node : graph.getNodes())
	{
		node.SetIsOnShortestPath(false);
	}

	IndexedPriorityQLow<double> pq(m_FCosts, graph.NumNodes());

	pq.insert(m_iSource);

	while (!pq.empty())
	{
		int NextClosestNode = pq.Pop();

		m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];

		if (NextClosestNode == m_iTarget) return;

		for (auto& pE : graph.GetEdgesByNode(NextClosestNode))
		{
			searchedEdges.push_back(&pE);

			double HCost = Heuristic_Euclid::Calculate(graph, m_iTarget, pE.To());
			double GCost = m_GCosts[NextClosestNode] + pE.Cost();

			if (m_SearchFrontier[pE.To()] == nullptr)
			{
				m_FCosts[pE.To()] = GCost + HCost;
				m_GCosts[pE.To()] = GCost;
				pq.insert(pE.To());
				m_SearchFrontier[pE.To()] = &pE;
			}
			else if (GCost < m_GCosts[pE.To()])
			{
				m_FCosts[pE.To()] = GCost + HCost;
				m_GCosts[pE.To()] = GCost;
				m_SearchFrontier[pE.To()] = &pE;
				pq.ChangePriority(pE.To());
				
			}
		}
	}
}

std::list<int> Graph_SearchAStar::GetPathToTarget()const
{
	for (auto& node : graph.getNodes())
	{
		node.SetIsOnShortestPath(false);
	}

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

	return path;
}