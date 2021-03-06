#include "SparseGraph.h"
#include "Graph_SearchAStar.h"

SparseGraph::SparseGraph(bool pDigraph) : nextNodeIndex(0), digraph(pDigraph)
{}

SparseGraph::~SparseGraph()
{
	delete bunnyPopulation;
	delete misterJansen;
	delete missesJansen;
	delete sheep;
}

const GraphNode& SparseGraph::GetNode(int idx) const
{
	return nodes[idx];
}

GraphNode& SparseGraph::GetNode(int idx)
{
	return nodes[idx];
}

const GraphEdge& SparseGraph::GetEdge(int from, int to) const
{
	for (auto& curEdge : edges)
	{
		for (auto& edge : curEdge)
		{
			if (edge.To() == to && edge.From() == from)
				return edge;
		}
	}
}

GraphEdge& SparseGraph::GetEdge(int from, int to)
{
	for (auto& curEdge : edges)
	{
		for (auto& edge : curEdge)
		{
			if (edge.To() == to && edge.From() == from)
				return edge;
		}
	}
}

std::vector<GraphEdge>& SparseGraph::GetEdgesByNode(int idx)
{
	return edges[idx];
};

int SparseGraph::AddNode(GraphNode node)
{
	if (node.Index() < (int) nodes.size())
	{
		nodes[node.Index()] = node;
		return nextNodeIndex;
	}

	else
	{
		nodes.push_back(node);
		edges.push_back(std::vector<GraphEdge>());

		return nextNodeIndex++;
	}
}

void SparseGraph::AddEdge(GraphEdge edge)
{
	if ((nodes[edge.To()].Index() != -1) && (nodes[edge.From()].Index() != -1))
	{
		edges[edge.From()].push_back(edge);

		if (!digraph)
		{
			GraphEdge NewEdge = edge;
			NewEdge.SetTo(edge.From());
			NewEdge.SetFrom(edge.To());
			edges[edge.To()].push_back(NewEdge);

		}
	}
}

bool SparseGraph::isNodePresent(int nd)const
{
	if ((nodes[nd].Index() == -1) || (nd >= (int)nodes.size()))
	{
		return false;
	}

	return true;
}

bool SparseGraph::isEdgePresent(int from, int to) const
{
	if (isNodePresent(from) && isNodePresent(from))
	{
		for (auto& curEdge : edges)
		{
			for (auto& edge : curEdge)
			{
				if (edge.To() == to)
					return true;
			}
		}
	}

	return false;
}

bool SparseGraph::Load(const char* FileName)
{
	std::ifstream in(FileName);

	if (!in)
	{
		throw std::runtime_error("Cannot open file: " + std::string(FileName));
		return false;
	}

	return Load(in);
}

bool SparseGraph::Load(std::ifstream& stream)
{
	nextNodeIndex = 0; 
	nodes.clear(); 
	edges.clear();

	int rows = 0;

	std::string line;
	std::getline(stream, line);
	std::vector<int> indexes(line.length(), -1);

	do
	{
		for (size_t i = 0; i < line.length(); i++)
		{
			if (line[i] != '~')
			{
				switch (line[i])
				{
					case 'X': AddNode(GraphNode(nextNodeIndex, Vector2D(i * 20, rows * 20), Color(0, 255, 0, 255), true)); break;
					case 'M':
					{
						AddNode(GraphNode(nextNodeIndex, Vector2D(i * 20, rows * 20), Color(255, 0, 0, 255), true));
						misterJansen = new MisterJansen(nextNodeIndex - 1, this);

						break;
					}
					case 'V':
					{
						AddNode(GraphNode(nextNodeIndex, Vector2D(i * 20, rows * 20), Color(255, 0, 255, 255), true));
						missesJansen = new MissesJansen(nextNodeIndex - 1, this);

						break;
					}
					case 'O':
					{
						AddNode(GraphNode(nextNodeIndex, Vector2D(i * 20, rows * 20), Color(125, 125, 125, 255), true));
						sheep = new Sheep(nextNodeIndex - 1, this);
						
						break;
					}
				}

				if (indexes[i] != -1)
				{
					AddEdge(GraphEdge(nextNodeIndex - 1, indexes[i], 20.f));
				}

				if (i != 0 && indexes[i - 1] != -1)
				{
					AddEdge(GraphEdge(nextNodeIndex - 1, indexes[i - 1], 20.f));
				}

				indexes[i] = nextNodeIndex - 1;
			}
			else
			{
				AddNode(GraphNode(nextNodeIndex, Vector2D(i * 20, rows * 20), Color(0, 0, 255, 255), false));
				indexes[i] = -1;
			}
		}

		rows++;
	} while (std::getline(stream, line));

	bunnyPopulation = new BunnyPopulation(this);
	bunnyPopulation->generateNewPopulation();

	return true;
}

void SparseGraph::resetNodes()
{
	for (auto& node : getNodes())
	{
		node.SetIsOnShortestPath(false);
		node.SetIsSearched(false);
	}
}

void SparseGraph::draw()
{
	FWApplication::GetInstance()->SetColor(Color(0, 255, 0, 255));

	for (auto& node : getNodes())
	{
		node.draw();
	}

	for (auto& edges : getEdges())
	{
		for (auto& edge : edges)
		{
			FWApplication::GetInstance()->SetColor(Color(0, 0, 0, 255));
			FWApplication::GetInstance()->DrawLine(GetNode(edge.From()).Pos().x + 10, GetNode(edge.From()).Pos().y + 10, GetNode(edge.To()).Pos().x + 10, GetNode(edge.To()).Pos().y + 10);
		}
	}

	misterJansen->draw();
	missesJansen->draw();
	sheep->draw();
	bunnyPopulation->draw();
}

void SparseGraph::update()
{
	misterJansen->update();
	missesJansen->update();
	sheep->update();
	bunnyPopulation->update();
}
