#pragma once

#include "SparseGraph.h"

class Heuristic_Euclid
{
public:
	static double Calculate(const SparseGraph& G, int nd1, int nd2)
	{
		return Vec2DDistance(G.GetNode(nd1).Pos(), G.GetNode(nd2).Pos());
	}
};