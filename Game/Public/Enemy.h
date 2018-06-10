#pragma once
#include "Engine/Public/EngineInterface.h"

class Enemy
{
public:
	Enemy(exEngineInterface* pEngine);

	virtual void Update(float deltaTime);


protected:
	exEngineInterface * mEngine;
	float				mTimeElapsed;
};
