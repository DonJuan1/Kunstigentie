#pragma once

#include "Vector2D.h"
#include "FWApplication.h"

class GraphNode
{

public:
	GraphNode() : index(-1){}
	GraphNode(int pIndex, Vector2D pos, Color pColor) : index(pIndex), position(pos) , color(pColor){}
	
	int Index() const 
	{ 
		return index; 
	} ;
	
	void SetIndex(int newIndex)
	{ 
		index = newIndex; 
	};

	Vector2D Pos() const
	{
		return position;
	}
	
	void SetPos(Vector2D newPosition)
	{
		position = newPosition;
	}

	void draw() const
	{
		FWApplication::GetInstance()->SetColor(color);
		FWApplication::GetInstance()->DrawRect((int)position.x, (int)position.y, 20, 20, true);
	}

private:
	int index;

	Vector2D position;
	Color color;
};

