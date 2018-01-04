#pragma once

class GraphEdge
{
public:
	GraphEdge(int from, int to, float cost) : cost(cost), from(from), to(to){}
	GraphEdge(int from, int to) : cost(1.f), from(from), to(to){}
	GraphEdge() : cost(1.f), from(-1), to(-1){}
	
	int From() const
	{
		return from;
	};

	void SetFrom(int newFrom)
	{
		from = newFrom;
	};
	
	int To() const
	{
		return to;
	};
	
	void SetTo(int newTo)
	{
		to = newTo;
	};
	
	float Cost() const
	{
		return cost;
	};

	void SetCost(float newCost)
	{
		cost = newCost;
	};

	bool operator==(const GraphEdge& rhs)
	{
		return rhs.from == this->from && rhs.to == this->to && rhs.cost == this->cost;
	}

	bool operator!=(const GraphEdge& rhs)
	{
		return !(*this == rhs);
	}

private:
	int from;
	int to;

	float cost;
};
