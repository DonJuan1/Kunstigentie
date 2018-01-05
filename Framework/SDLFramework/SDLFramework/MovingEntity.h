#pragma once

#include <vector>

#include "BaseEntity.h"
#include "Vector2D.h"

class SparseGraph;

class MovingEntity : public BaseEntity
{
protected:
	Vector2D velocity;
	Vector2D heading = Vector2D(1, 1);
	Vector2D side = Vector2D(-1, 1);

	bool tag;

	float mass = 0.1f;
	float maxSpeed = 100.f;
	float maxForce = 800.f;
	float collisionRadius = 3.f;

	float attractionToScheep = 1;
	float attractionToWater = 0;
	float separation = 1;
	float alignment = 1;
	float cohesion = 1;

public:
	MovingEntity(SparseGraph* graph) : BaseEntity(graph) {};

	Vector2D Velocity() const
	{
		return velocity;
	}

	Vector2D Heading() const
	{
		return heading;
	}

	Vector2D Side() const
	{
		return side;
	}

	void Tag()
	{
		tag = true;
	}

	void UnTag()
	{
		tag = false;
	}

	bool IsTagged() const
	{
		return tag;
	}

	float Mass()
	{
		return mass;
	}

	float MaxSpeed() const
	{
		return maxSpeed;
	}

	float MaxForce() const
	{
		return maxForce;
	}

	float CollisionRadius() const
	{
		return collisionRadius;
	}

	float getAttractionToWater() const
	{
		return attractionToWater;
	}

	void setAttractionToWater(float atw)
	{
		attractionToWater = atw;
	}

	float getAttractionToSheep() const
	{
		return attractionToScheep;
	}

	void setAttractionToSheep(float ats)
	{
		attractionToScheep = ats;
	}

	float getSeparation() const
	{
		return separation;
	}

	void setSeparation(float sep)
	{
		separation = sep;
	}

	float getAlignment() const
	{
		return alignment;
	}

	void setAlignment(float ali)
	{
		alignment = ali;
	}

	float getCohesion() const
	{
		return cohesion;
	}

	void setCohesion(float coh)
	{
		cohesion = coh;
	}
};

