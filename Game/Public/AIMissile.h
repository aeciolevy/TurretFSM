#pragma once
#include "Engine\Public\EngineInterface.h"
#include "Game/Public/Help.h"
#include "Game/Public/Factory.h"

const float TIME_TO_LAUCH = 5.0f;

class AIMissile
{
public:
	AIMissile(exEngineInterface* pEngine, std::vector<exVector2> citiesPosition)
		: mEngine(pEngine)
	{
		mTimeToLaunch = TIME_TO_LAUCH;
		mCitiesPosition = citiesPosition;
	}
	~AIMissile();

	void LaunchMissile()
	{	
		int cityToAttack = Help::GenerateRandom(0, (int) mCitiesPosition.size() - 1);
		exVector2 finalPosition = mCitiesPosition[cityToAttack];
		Factory::Instance()->CreateMissiles(mEngine, Help::EnemyMissileStartPosition(), { finalPosition.x + 15.0f, finalPosition.y }, GameObjectType::MissileEnemy);
	}

	void Update(float deltaTime) 
	{
		mTimeToLaunch -= deltaTime;
		if (mTimeToLaunch <= 0)
		{
			LaunchMissile();
			mTimeToLaunch = TIME_TO_LAUCH;
		}
	}

private:
	float						mTimeToLaunch;
	exEngineInterface*			mEngine;
	std::vector<exVector2>		mCitiesPosition;
};
