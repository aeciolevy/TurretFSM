#include "Game\Public\COGExplosionController.h"
#include "Game\Public\Factory.h"

std::vector<COGExplosionController*> COGExplosionController::mExplosionControllerComponents;

COGExplosionController::COGExplosionController(GameObject* pGO, COGTransform* pTransform, float radius)
	: Component(pGO)
{
	mGO = pGO;
	mExplosion = pGO->FindComponent<COGExplosion>(ComponentType::Explosion);
	mTransform = pTransform;
	mVelocity = 10.0f;
	mRadius = 0.0;
	mFinalRadius = radius;
}

bool COGExplosionController::ReachFinalPosition()
{
	if (mRadius >= mFinalRadius)
	{
		return true;
	}
	return false;
}


void COGExplosionController::Update(float DeltaTime)
{
	if (ReachFinalPosition() == false)
	{
		mRadius += mVelocity * DeltaTime;
		mExplosion->SetRadius(mRadius);
	}
	else
	{
		Factory::Instance()->addToStaleList(mGO);
	}
}