#include "Bunny.h"
#include "FWApplication.h"
#include "BunnyPopulation.h"
#include "SparseGraph.h"
#include <iostream>

void Bunny::tagNeighborBunnies(std::vector<Bunny*>& entities)
{
	for (auto currentEntity : entities)
	{
		currentEntity->UnTag();

		Vector2D to = currentEntity->getPosition() - position;
		float range = visibilityRadius + currentEntity->getVisibilityRadius();

		if (currentEntity != this && (to.LengthSq()) < range*range)
		{
			currentEntity->Tag();
		}
	}
}

void Bunny::draw()
{
	FWApplication::GetInstance()->SetColor(Color(117, 59, 11, 255));
	FWApplication::GetInstance()->DrawRect((int)position.x - 2.5, (int)position.y - 2.5, 5, 5, true);
	FWApplication::GetInstance()->DrawLine((int)position.x, (int) position.y, position.x + heading.x * 10 , position.y + heading.y * 10);
}

void Bunny::update()
{
	int bunnyXPosition = static_cast<int>(position.x);
	int bunnyYPosition = static_cast<int>(position.y);
	Vector2D bunnyNodePosition = Vector2D(bunnyXPosition - bunnyXPosition % 20, bunnyYPosition - bunnyYPosition % 20);

	GraphNode* node = graph->getNodesAtPosition(bunnyNodePosition);
	if (node == nullptr)
	{
		isAlive = false;
		return;
	}
	else
	{
		if (graph->GetNode(graph->getSheep()->getNodeIndex()).Pos().DistanceSq(node->Pos()) < 15 * 15)
		{
			isAlive = false;
			return;
		}

		if (!node->IsWalkable())
		{
			isAlive = false;
			return;
		}
	}

	timeAlive += FWApplication::GetInstance()->GetDeltaTime();

	Vector2D SteeringForce = steering->Calculate();

	Vector2D acceleration = SteeringForce / mass;

	velocity += acceleration * FWApplication::GetInstance()->GetDeltaTime() / 1000;

	velocity.Truncate(maxSpeed);

	position += velocity * FWApplication::GetInstance()->GetDeltaTime() / 1000;

	if (velocity.LengthSq() > 0.00000001)
	{
		heading = Vec2DNormalize(velocity);
		side = heading.Perp();
	}

	steering->EnforceNonPenetrationConstraint(graph->getBunnyPopulation()->getBunnies());
}
