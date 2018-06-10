#pragma once
#include "Game\Public\COGInput.h"
#include "Game\Public\Help.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGFSM.h"


class COGShootInput : public COGInput
{
public:
	COGShootInput(exEngineInterface* pEngine, GameObject* pGO)
		: COGInput(pGO)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mFSM = pGO->FindComponent<COGFSM>(ComponentType::FSM);
	}

	virtual ComponentType GetType() const { return ComponentType::ShootInput; }

	virtual void ChangeState();

	virtual void Update() override;
	

private:
	exVector2			mPosition;
	exEngineInterface*	mEngine;
	COGTransform*		mTransform;
	COGFSM*				mFSM;
	bool				mMouseClick;
	bool				mSpacePressed;
};