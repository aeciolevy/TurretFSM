#pragma once
#include "Game\Public\GameObject.h"

class FSMState;

enum class State : int 
{
	Normal,
	BigShoot
};

class COGFSM : public Component
{
public:

	static std::vector<COGFSM*> mFSMComponents;

public:

	COGFSM(GameObject* pGO);
	~COGFSM();

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual ComponentType GetType() const;

	void Start(FSMState* pState, State newState);
	void Next(FSMState* pState, State newState);

	void Update(float fDeltaT);

	State mState;

	template<class T>
	T* Create()
	{
		return new T(this);
	}

private:

	GameObject * mGO;		// this could be the COG that contains the FSM

	FSMState* mCurrent;
	FSMState* mNext;

};