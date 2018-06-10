#include "Game/Public/COGFSM.h"
#include "Game/Public/FSMState.h"

std::vector<COGFSM*> COGFSM::mFSMComponents;


COGFSM::COGFSM(GameObject* pGO)
	: Component(pGO)
	, mGO(pGO)
	, mCurrent(nullptr)
	, mNext(nullptr)
{
}

COGFSM::~COGFSM()
{
}

void COGFSM::Initialize()
{	
	AddToComponentVector(mFSMComponents);	
}

void COGFSM::Destroy() 
{
	RemoveFromComponentVector(mFSMComponents);
}

ComponentType COGFSM::GetType() const
{ 
	return ComponentType::FSM; 
}

void COGFSM::Start(FSMState* pState, State newState)
{
	// assert when mCurrent is not null?
	mCurrent = pState;
	mState = newState;
}

void COGFSM::Next(FSMState* pState, State newState)
{
	if (mNext != nullptr)
	{
		delete mNext;
	}
	mState = newState;
	mNext = pState;
}

void COGFSM::Update(float fDeltaT)
{
	if (mNext != nullptr)
	{
		mCurrent->OnExit();
		delete mCurrent;

		mCurrent = mNext;
		mCurrent->OnEnter();

		mNext = nullptr;
	}

	mCurrent->Update(fDeltaT);
}
