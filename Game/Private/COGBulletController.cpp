#include "Game/Public/COGBulletController.h"
#include "Game/Public/Factory.h"

void COGBulletController::CalculateDirection()
{
	mDirection = mPosition.Sub(mStartWeaponPos);
	mDirection = mDirection.Normalize();
}

void COGBulletController::Update(float deltaTime)
{
	mPosition.x += mDirection.x * velocity * deltaTime;
	mPosition.y += mDirection.y * velocity * deltaTime;
	mTransform->SetPosition(mPosition);
	
}