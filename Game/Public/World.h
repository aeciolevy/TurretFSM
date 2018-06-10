#pragma once
#include "Game\Public\GameObject.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGBounce.h"
#include "Game\Public\COGMissileController.h"
#include "Game\Public\COGExplosionController.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Enemy.h"

class Factory;
// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	World(exEngineInterface* pEngine);

	void Initialize();

	void Destroy();

	void Update(float fDeltaT);

	virtual void DrawGameOver();

	virtual void MouseClick();

	virtual void LauchMissile();

private:

	std::vector<GameObjectHandle>		mGameObjects;
	exEngineInterface*					mEngine;
	exVector2							mMousePosition;
	Factory*							mFactory;
	Enemy*								mEnemy;
	int									mMouseLeft;
	bool								mMouseLeftOld;
};
