#pragma once
#include "Game\Public\COGInput.h"
#include "Game\Public\Help.h"
#include "Game\Public\COGTransform.h"


//class Factory;

class COGShootInput : public COGInput
{
public:
	COGShootInput(exEngineInterface* pEngine, GameObject* pGO)
		: COGInput(pGO)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
	}

	virtual ComponentType GetType() const { return ComponentType::ShootInput; }

	virtual void Update() override;
	

private:
	exVector2			mPosition;
	exEngineInterface*	mEngine;
	COGTransform*		mTransform;
	bool				mMouseClick;
};