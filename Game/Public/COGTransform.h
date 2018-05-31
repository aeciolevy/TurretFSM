#pragma once
#include "Game\Public\GameObject.h"
#include "Engine/Public/EngineTypes.h"

class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO, exVector2 startPosition)
		: Component(pGO)
	{
		mPosition = startPosition;
	}

	virtual ComponentType GetType() const { return ComponentType::Transform; }

	exVector2& GetPosition() { return mPosition; }

	exVector2& GetFinalPos() { return mFinalPos; }

	void SetFinalPos(exVector2 finalPosition) 
	{
		mFinalPos = finalPosition;
	}

	void ResetPosition(exVector2 newPosition)
	{
		mPosition = newPosition;
	}

private:
	
	exVector2 mFinalPos;
	exVector2 mPosition;

};