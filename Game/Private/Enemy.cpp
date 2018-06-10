#include "Game/Public/Enemy.h"
#include "Game/Public/Factory.h"
#include "Game/Public/Help.h"

Enemy::Enemy(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mTimeElapsed = 5.0f;
}

void Enemy::Update(float deltaTime)
{
	mTimeElapsed -= deltaTime;
	if (mTimeElapsed <= 0)
	{
		float yPos = (float)Help::GenerateRandom(100, 500);
		Factory::Instance()->CreateGameObject(mEngine, { 800.0f, yPos }, GameObjectType::Enemy);
		mTimeElapsed = 5.0f;
	}
}