#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\Output.h"

// COGBounce - where we make the ball bounce
class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Bounce; }

	// r = d - 2*(d dot n) * n
	virtual exVector2 CalculateResultVector(exVector2 incidentVector, exVector2 normal)
	{
		float factor = incidentVector.Dot(normal);
		exVector2 part2Equation = normal.MultVectorByFactor(factor);
		exVector2 part2Mult = part2Equation.MultVectorByFactor(2);
		exVector2 result = incidentVector.Sub(part2Mult);
		return result;
	}

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override
	{
		/*exVector2 velocity = pMe->GetVelocity();
		exVector2 result = CalculateResultVector(velocity, normal);
		pMe->SetVelocity(result);*/
	}

};
