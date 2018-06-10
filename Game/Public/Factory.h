#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineInterface.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\COGBoxShape.h"
#include "Game\Public\COGBulletController.h"
#include "Game\Public\COGShootInput.h"
#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGLineShape.h"
#include "Game\Public\COGExplosion.h"
#include "Game\Public\COGExplosionController.h"
#include "Game\Public\COGMissileController.h"
#include "Game\Public\GameObjectInventory.h"
#include "Game\Public\FSMNormalBullet.h"
#include "Game\Public\COGFSM.h"
#include "Game\Public\COGEnemyController.h"

class COGMissileController;


extern std::hash<std::string> s_hash;

enum class GameObjectType : int
{
	Turret = 0,
	Bullet,
	BigBullet,
	Base,
	Enemy,
	MissileFriend,
	Missile,
	MissileEnemy,
	Explosion,
};

class GameObjectInventory;
class GameObjectHandle;
class GameObject;

class Factory : public Singleton<Factory>
{
	
public:
	int mCities;
	friend class Singleton<Factory>;
	
	Factory()
		: mIdentify(0)
	{
	}

	GameObject* CreateGameObject(exEngineInterface* pEngine, exVector2 startPosition, GameObjectType gameType);

	GameObject* CreateTurret(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);
	GameObject* CreateBullet(Hash hash, exEngineInterface* pEngine, exVector2 startPosition, float Radius);
	GameObject* CreateExplosion(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);
	GameObject* CreateAI(Hash hash, exEngineInterface* pEngine, exVector2 startPosition);

	void addToStaleList(GameObject* gameObject);
	void cleanStaleList();
	
private:
	
	std::vector<GameObject*>	mStaleGameObjects;
	int							mIdentify;
	exVector2					mTurretWeaponStartPos;
};