#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGTransform.h"

class COGExplosion;

class COGExplosionController : public Component
{
public:
	static std::vector<COGExplosionController*> mExplosionControllerComponents;
public:

	COGExplosionController(GameObject* pGO, COGTransform* pTransform, float radius);

	virtual ComponentType GetType() const { return ComponentType::ExplosionController; }

	virtual void Initialize() override
	{
		AddToComponentVector(mExplosionControllerComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mExplosionControllerComponents);
	}

	bool ReachFinalPosition();

	virtual void Update(float DeltaTime);


private:

	float						mVelocity;
	float						mRadius;
	float						mFinalRadius;
	COGTransform *				mTransform;
	bool						mFinish;
	COGExplosion*				mExplosion;
	GameObject*					mGO;
	ComponentType				mType;
};