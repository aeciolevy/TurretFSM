#pragma once
#include "Game\Public\GameObject.h"
#include "Engine\Public\EngineInterface.h"

class COGController : public Component
{
public:

	static std::vector<COGController*> mControllerComponents;

public:

	COGController(GameObject* pGO)
		:Component(pGO)
	{
	}

	virtual void Initialize() override
	{
		AddToComponentVector(mControllerComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mControllerComponents);
	}

	virtual void Update(float deltaTime) = 0;

protected:
	exEngineInterface * mEngine;

};