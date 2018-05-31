#pragma once
#include "Engine\Public\EngineInterface.h"
#include "Game\Public\GameObject.h"

class COGTurret : public Component
{
public:
	COGTurret(exEngineInterface* pEngine, GameObject* pGO, exVector2 startPosition)
		: Component(pGO)
	{
	}

private:
	exEngineInterface * mEngine;
	GameObject*			mGO;
	exVector2			mPosition;
};
