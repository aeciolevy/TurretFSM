#include "Game/Public/COGEnemyController.h"

void COGEnemyController::Update(float deltaTime)
{
	mPosition.x += mDirection.x * velocity * deltaTime;
	SetY();
	mPosition.y += mDirection.y * velocity * deltaTime;
	mTransform->SetPosition(mPosition);
}

void COGEnemyController::SetY()
{
	if (mPosition.y <= 250.0f)
	{
		mDirection.y = 1.0f;
	}
	else if (mPosition.y >= 330.0f)
	{
		mDirection.y = -1.0f;
	}
}