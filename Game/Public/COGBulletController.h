#pragma once
#include "Game\Public\COGController.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\Output.h"

class COGBulletController : public COGController
{
public:
	COGBulletController(GameObject* pGO)
		: COGController(pGO)
	{
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mPosition = mTransform->GetPosition();
		mDirection = mPosition.VectorDirection();
		exOutputTransform(mDirection.y);
		velocity = 10;
	}

	virtual ComponentType GetType() const { return ComponentType::BulletController; }

	virtual void Update(float deltaTime) override
	{
		mPosition.x += mDirection.x * velocity * deltaTime;
		mPosition.y += mDirection.y * velocity * deltaTime;
		mTransform->SetPosition(mPosition);
	}

private:
	COGTransform *		mTransform;
	exVector2			mPosition;
	exVector2			mDirection;
	float				velocity;
};