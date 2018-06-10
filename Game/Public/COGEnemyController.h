#pragma once
#include "Game\Public\COGController.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\Output.h"

class COGEnemyController : public COGController
{
public:
	COGEnemyController(exEngineInterface* pEngine, GameObject* pGO)
		: COGController(pGO)
	{
		mGO = pGO;
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		// Position bullet lauched
		mPosition = mTransform->GetPosition();
		velocity = 120;	
		mDirection = { -1, 1 };
	}

	virtual ComponentType GetType() const { return ComponentType::EnemyController; }

	virtual void SetY();

	virtual void Update(float deltaTime) override;


private:
	exEngineInterface * mEngine;
	GameObject *		mGO;
	COGTransform *		mTransform;
	exVector2			mPosition;
	exVector2			mDirection;
	exVector2			mStartWeaponPos;
	float				velocity;
};