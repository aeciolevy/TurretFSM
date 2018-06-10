#pragma once
#include "Game\Public\GameObject.h"
#include "Engine\Public\EngineInterface.h"

class COGInput : public Component
{
public:

	static std::vector<COGInput*> mInputComponents;

public:

	COGInput(GameObject* pGO)
		:Component(pGO)
	{
	}

	virtual void Initialize() override
	{
		AddToComponentVector(mInputComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mInputComponents);
	}

	virtual void Update() = 0;

protected:
	exEngineInterface * mEngine;

};