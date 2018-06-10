#pragma once
#include "Game/Public/FSMState.h"

class FSMNormalBullet : public FSMState
{
public:
	FSMNormalBullet(COGFSM* pFSM) 
		: FSMState(pFSM)
	{
		mState = State::Normal;
	}

	virtual void Update(float fDeltaT) override
	{
	}

private:
	State	mState;
};