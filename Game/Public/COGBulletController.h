#pragma once
#include "Game\Public\COGController.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\Output.h"

class COGBulletController : public COGController
{
public:
	COGBulletController(GameObject* pGO, exVector2 weaponStartPosition)
		: COGController(pGO)
	{
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		// Position bullet lauched
		mPosition = mTransform->GetPosition();
		mStartWeaponPos = weaponStartPosition;
		velocity = 80;
		CalculateDirection();
	}

	virtual ComponentType GetType() const { return ComponentType::BulletController; }

	virtual void CalculateDirection();

	virtual void Update(float deltaTime) override;


private:
	COGTransform *		mTransform;
	exVector2			mPosition;
	exVector2			mDirection;
	exVector2			mStartWeaponPos;
	float				velocity;
};