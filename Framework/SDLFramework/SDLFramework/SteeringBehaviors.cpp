#include "SteeringBehaviors.h"
#include "Bunny.h"
#include "RandomGenerator.h"
#include "BunnyPopulation.h"
#include "SparseGraph.h"
#include <iostream>

const float TwoPi = 3.14159 * 2;

SteeringBehaviors::SteeringBehaviors(Bunny * pBunny) : bunny(pBunny)
{
	float theta = RandomGenerator::getInstance().generateFloat(-1.f, 1.f) * TwoPi;

	wanderTarget = Vector2D(wanderRadius * cos(theta), wanderRadius * sin(theta));
	wanderTarget.Normalize();
}

Vector2D SteeringBehaviors::Seek(Vector2D TargetPos)
{
	Vector2D DesiredVelocity = Vec2DNormalize(TargetPos - bunny->getPosition()) * bunny->MaxSpeed();
	return (DesiredVelocity - bunny->Velocity());
}

Vector2D SteeringBehaviors::Free(Vector2D TargetPos)
{
	Vector2D DesiredVelocity = Vec2DNormalize(bunny->getPosition() - TargetPos) * bunny->MaxSpeed();
	return (DesiredVelocity - bunny->Velocity());
}

Vector2D SteeringBehaviors::Arrive(Vector2D TargetPos, int pSpeed)
{
	Vector2D ToTarget = TargetPos - bunny->getPosition();

	float distance = ToTarget.Length();

	if (distance > 0)
	{
		float speed = distance / pSpeed;

		speed = min(speed, bunny->MaxSpeed());

		Vector2D DesiredVelocity = ToTarget * speed / distance;
		return (DesiredVelocity - bunny->Velocity());
	}

	return Vector2D();
}

Vector2D SteeringBehaviors::Wander()
{
	Vector2D target = wanderTarget * wanderRadius;
	target += Vector2D(RandomGenerator::getInstance().generateFloat(-1.f, 1.f) * wanderJitter, RandomGenerator::getInstance().generateFloat(-1.f, 1.f) * wanderJitter);
	target.Normalize();

	wanderTarget = target;

	target = bunny->getPosition() + (bunny->Heading() * wanderDistance) + (target * wanderRadius);
	
	FWApplication::GetInstance()->SetColor(Color(51, 51, 51, 255));
	FWApplication::GetInstance()->DrawRect(target.x + 2.5 , target.y + 2.5, 5, 5, true);

	return Seek(target);
}

Vector2D SteeringBehaviors::Separation(const std::vector<Bunny*>& neighbors)
{
	Vector2D steeringforce;

	for (auto neighbor : neighbors)
	{
		if (neighbor != bunny && neighbor->IsTagged())
		{
			Vector2D toEntity = bunny->getPosition() - neighbor->getPosition();
			if (toEntity.x != 0 && toEntity.y)
			{
				steeringforce += Vec2DNormalize(toEntity) / toEntity.Length();
			}
		}
	}

	return steeringforce;
}

Vector2D SteeringBehaviors::Alignment(const std::vector<Bunny*>& neighbors)
{
	Vector2D averageHeading;

	int neighborCount = 0;

	for (auto neighbor : neighbors)
	{
		if (neighbor != bunny && neighbor->IsTagged())
		{
			averageHeading += neighbor->Heading();
			neighborCount++;
		}
	}

	if (neighborCount > 0)
	{
		averageHeading /= (double)neighborCount;
		averageHeading -= bunny->Heading();
	}

	return averageHeading;
}

Vector2D SteeringBehaviors::Cohesion(const std::vector<Bunny*>& neighbors)
{
	Vector2D centerOfMass, steeringForce;

	int neighborCount = 0;

	for (auto neighbor : neighbors)
	{
		if (neighbor != bunny && neighbor->IsTagged())
		{
			centerOfMass += neighbor->getPosition();

			++neighborCount;
		}
	}

	if (neighborCount > 0)
	{
		centerOfMass /= (double) neighborCount;
		steeringForce = Seek(centerOfMass);
	}

	return Vec2DNormalize(steeringForce);
}

Vector2D SteeringBehaviors::Calculate()
{
	Vector2D SteeringForce;
	Vector2D force;

	bunny->tagNeighborBunnies(bunny->getGraph()->getBunnyPopulation()->getBunnies());
	
	force += Separation(bunny->getGraph()->getBunnyPopulation()->getBunnies());
	if (!AccumulateForce(SteeringForce, force)) return SteeringForce;

	force += Alignment(bunny->getGraph()->getBunnyPopulation()->getBunnies()) * 0.5f;
	if (!AccumulateForce(SteeringForce, force)) return SteeringForce;

	force += Cohesion(bunny->getGraph()->getBunnyPopulation()->getBunnies());
	if (!AccumulateForce(SteeringForce, force)) return SteeringForce;

	force += Vec2DNormalize(Wander()) * 2.f;
	if (!AccumulateForce(SteeringForce, force)) return SteeringForce;

	SteeringForce.Truncate(bunny->MaxForce());
	return SteeringForce;
}

bool SteeringBehaviors::AccumulateForce(Vector2D& steeringForce, Vector2D newForceToAdd)
{
	double magnitude_so_far = steeringForce.Length();

	double magnitude_remaining = bunny->MaxForce() - magnitude_so_far;

	//return false if there is no more force left to use
	if (magnitude_remaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	double magnitude_to_add = newForceToAdd.Length();

	//now calculate how much of the force we can really add
	if (magnitude_to_add > magnitude_remaining)
	{
		magnitude_to_add = magnitude_remaining;
	}

	//add it to the steering force
	steeringForce += (Vec2DNormalize(newForceToAdd) * magnitude_to_add);

	return true;
}

void SteeringBehaviors::EnforceNonPenetrationConstraint(const std::vector<Bunny*>& neighbors)
{
	for (auto entity : neighbors)
	{
		if (entity == this->bunny) continue;

		Vector2D to = bunny->getPosition() - entity->getPosition();

		float distance = to.Length();

		float amount_of_overlap = bunny->CollisionRadius() + entity->CollisionRadius() - distance;

		if (amount_of_overlap >= 0)
		{
			bunny->setPosition(bunny->getPosition() + (to / distance) * amount_of_overlap);
		}
	}
}
