#pragma once

#include <vector>

#include "Vector2D.h"
#include "FWApplication.h"

class Bunny;

class SteeringBehaviors
{
private:
	Bunny* bunny;
	Vector2D wanderTarget;

	float wanderRadius = 60.f;
	float wanderDistance = 30.f;
	float wanderJitter = 40.f;

public:
	SteeringBehaviors(Bunny* pBunny);

	Vector2D SteeringBehaviors::Seek(Vector2D TargetPos);
	Vector2D SteeringBehaviors::Free(Vector2D TargetPos);
	Vector2D SteeringBehaviors::Arrive(Vector2D TargetPos, int speed);
	Vector2D SteeringBehaviors::Wander();
	Vector2D SteeringBehaviors::NodeAvoidens();

	Vector2D SteeringBehaviors::Separation(const std::vector<Bunny*>& neighbors);
	Vector2D SteeringBehaviors::Alignment(const std::vector<Bunny*>& neighbors);
	Vector2D SteeringBehaviors::Cohesion(const std::vector<Bunny*>& neighbors);

	Vector2D Calculate();
	bool AccumulateForce(Vector2D& steeringForce, Vector2D newForceToAdd);
	void EnforceNonPenetrationConstraint(const std::vector<Bunny*>& neighbors);
};

