#pragma once
#include "Game/Public/COGFSM.h"

class COGFSM;

class FSMState
{
public:

	FSMState(COGFSM* pFSM);
	virtual ~FSMState();

	virtual void OnEnter();			// gets called when enters
	virtual void OnExit();		// gets called when exits

	virtual void Update(float fDeltaT);

protected:

	COGFSM * mFSM;
	State	 mState;
};