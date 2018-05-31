#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"
#include "Engine\Public\EngineInterface.h"

class COGMissileController : public Component
{
public:
	static std::vector<COGMissileController*> mMissileControllerComponents;
public:

	COGMissileController(GameObject* pGO, COGTransform* pTransform, exEngineInterface* pEngine);

	virtual ComponentType GetType() const { return ComponentType::MissileController; }
	
	virtual void Initialize() override
	{
		AddToComponentVector(mMissileControllerComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mMissileControllerComponents);
	}

	void SetVectorToMissile(exVector2 finalPosition);

	bool ReachFinalPosition();

	virtual void Update(float DeltaTime);


private:
	exEngineInterface *			mEngine;
	exVector2					mFinalPosition;
	exVector2					mPosition;
	exVector2					mUnitVector;
	exVector2					mDirection;
	COGTransform *				mTransform;
	float						mVelocity;
	bool						mFinish;
	GameObject*					mGO;
	ComponentType				mType;
};