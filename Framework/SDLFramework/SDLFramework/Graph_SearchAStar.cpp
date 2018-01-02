#include "Graph_SearchAStar.h"


void Graph_SearchAStar::Search()
{
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
			else if ((GCost < m_GCosts[pE.To()]) && (m_ShortestPathTree[pE.To()] == nullptr))
			{
				m_FCosts[pE.To()] = GCost + HCost;
				m_GCosts[pE.To()] = GCost;
				pq.ChangePriority(pE.To());
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
			return path;
		}

		path.push_front(nd);
	}

	return path;
}