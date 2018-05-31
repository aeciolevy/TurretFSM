#include "Game\Public\COGMissileController.h"
#include "Game\Public\Factory.h"

std::vector<COGMissileController*> COGMissileController::mMissileControllerComponents;

COGMissileController::COGMissileController(GameObject* pGO, COGTransform* pTransform, exEngineInterface* pEngine)
	: Component(pGO)
	, mEngine(pEngine)
{
	mGO = pGO;
	mTransform = pTransform;
	mPosition = pTransform->GetPosition();
	mVelocity = 80.0f;
}

bool COGMissileController::ReachFinalPosition()
{
	if (mDirection.x > 0)
	{
		if (mPosition.x >= mFinalPosition.x)
		{
			return true;
		}
	}
	else
	{
		if (mPosition.x <= mFinalPosition.x)
		{
			return true;
		}
	}
	return false;
}

void COGMissileController::SetVectorToMissile(exVector2 finalPosition)
{
	mFinalPosition = finalPosition;
	mUnitVector = mPosition.GetVector(mFinalPosition);
	mUnitVector = mUnitVector.Normalize();
	mDirection = mUnitVector.VectorDirection();
}

void COGMissileController::Update(float DeltaTime)
{
	if (ReachFinalPosition() == false)
	{
		mPosition.x += mUnitVector.x * mVelocity * DeltaTime;
		mPosition.y += mUnitVector.y * mVelocity * DeltaTime;
		mTransform->SetFinalPos(mPosition);
	}
	else
	{
		Factory::Instance()->addToStaleList(mGO);
		Factory::Instance()->CreateGameObject(mEngine, mFinalPosition, GameObjectType::Explosion);
	}
}