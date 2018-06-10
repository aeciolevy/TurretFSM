#include "Game\Public\Factory.h"

Factory* Singleton<Factory>::mSingleton = nullptr;
std::hash<std::string> s_hash;



GameObject* Factory::CreateGameObject(exEngineInterface* pEngine, exVector2 startPosition, GameObjectType gameType)
{
	GameObject* newGameObject;
	++mIdentify;
	switch (gameType)
	{
	case GameObjectType::Turret:
	{
		return newGameObject = CreateTurret(s_hash("Turret" + std::to_string(mIdentify)), pEngine, startPosition);
	}
	case GameObjectType::Bullet:
	{
		return newGameObject = CreateBullet(s_hash("Bullet" + std::to_string(mIdentify)), pEngine, startPosition);
	}
	case GameObjectType::Explosion:
		return newGameObject = CreateExplosion(s_hash("Explosion" + std::to_string(mIdentify)), pEngine, startPosition);
	default:
		std::cout << "Wrong type" << std::endl;
		return nullptr;
	}
	return nullptr;
}

GameObject* Factory::CreateTurret(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
{
	const float TURRET_WIDTH = 30.0f;
	const float TURRET_HEIGHT = 80.0f;

	exColor turretColor;
	exColor gunColor;
	turretColor.SetColor(64, 22, 153, 255);
	gunColor.SetColor(255, 255, 255, 255);

	GameObject* turret = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(turret, startPosition);
	turret->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pEngine, turret, TURRET_WIDTH, TURRET_HEIGHT, turretColor);
	turret->AddComponent(pBoxShape);

	exVector2 gunPosition = { startPosition.x + TURRET_WIDTH, startPosition.y + TURRET_HEIGHT / 2.0f };

	COGLineShape* pLine = new COGLineShape(pEngine, turret, gunPosition, gunColor);
	turret->AddComponent(pLine);

	COGPhysics* pPhysics = new COGPhysics(turret, true, GameObjectType::Turret);
	turret->AddComponent(pPhysics);

	COGShootInput* pShoot = new COGShootInput(pEngine, turret);
	turret->AddComponent(pShoot);

	turret->Initialize();

	return turret;
}

GameObject* Factory::CreateBullet(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
{
	exColor bulletColor;
	bulletColor.SetColor(255, 255, 255, 255);

	float Radius = 20.0f;

	GameObject* bullet = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(bullet, startPosition);
	bullet->AddComponent(pTransform);

	COGBulletController* pController = new COGBulletController(bullet);
	bullet->AddComponent(pController);

	COGCircleShape* pShape = new COGCircleShape(pEngine, bullet, Radius);
	bullet->AddComponent(pShape);

	COGPhysics* pPhysics = new COGPhysics(bullet, true, GameObjectType::Bullet);
	bullet->AddComponent(pPhysics);

	bullet->Initialize();

	return bullet;
}

GameObject* Factory::CreateMissiles(exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition, GameObjectType gameType) 
{
	//GameObject* newGameObject;
	//++mIdentify;
	//switch (gameType)
	//{
	//case GameObjectType::MissileFriend:
	//{
	//	exColor friendColor;
	//	friendColor.SetColor(255, 255, 255, 255);
	//	return newGameObject = CreateMissile(s_hash("Missile" + std::to_string(mIdentify)), pEngine, startPosition, finalPosition, friendColor, false, GameObjectType::MissileFriend);
	//}
	//case GameObjectType::MissileEnemy:
	//{
	//	exColor enemyColor;
	//	enemyColor.SetColor(200, 0, 20, 255);
	//	return newGameObject = CreateMissile(s_hash("MissileEnemy" + std::to_string(mIdentify)), pEngine, startPosition, finalPosition, enemyColor, true, GameObjectType::MissileEnemy);
	//}
	//default:
	//	std::cout << "Wrong type" << std::endl;
	//	return nullptr;
	//}
	return nullptr;
}

GameObject* Factory::CreateExplosion(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
{
	exColor explosionColor;
	explosionColor.mColor[0] = 255;
	explosionColor.mColor[1] = 255;
	explosionColor.mColor[2] = 196;
	explosionColor.mColor[3] = 255;

	float Radius = 40.0f;

	GameObject* explosion = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(explosion, startPosition);
	explosion->AddComponent(pTransform);

	COGExplosion* pExplosion = new COGExplosion(pEngine, explosion, pTransform, startPosition, explosionColor);
	explosion->AddComponent(pExplosion);

	COGExplosionController* pExplosionController = new COGExplosionController(explosion, pTransform, Radius);
	explosion->AddComponent(pExplosionController);

	COGPhysics* pPhysics = new COGPhysics(explosion, true, GameObjectType::Explosion);
	explosion->AddComponent(pPhysics);

	explosion->Initialize();

	return explosion;
}

void Factory::addToStaleList(GameObject* gameObject)
{
	if (gameObject->GetHandle().IsValid())
	{
		if (gameObject->FindComponent<COGBoxShape>(ComponentType::BoxShape) != nullptr)
		{
			--mCities;
		}
		mStaleGameObjects.push_back(gameObject);
	}
}

void Factory::cleanStaleList()
{
	if (mStaleGameObjects.size() > 0)
	{
		for (int i = 0; i < (int)mStaleGameObjects.size(); ++i)
		{
			GameObjectInventory::Instance()->Unregister(mStaleGameObjects[i]);
			mStaleGameObjects.erase(mStaleGameObjects.begin() + i);
		}
	}
}