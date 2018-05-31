#include "Game\Public\Factory.h"

Factory* Singleton<Factory>::mSingleton = nullptr;
int Factory::mMissiliesAvailable = 25;
std::hash<std::string> s_hash;

GameObject* Factory::CreateCity(Hash hash, exEngineInterface* pEngine, exVector2 startPosition)
{
	const float CITY_WIDTH = 50.0f;
	const float CITY_HEIGHT = 10.0f;

	exColor cityColor;
	cityColor.SetColor(64, 22, 153, 255);

	GameObject* city = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(city, startPosition);
	city->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pEngine, city, CITY_WIDTH, CITY_HEIGHT, cityColor);
	city->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(city, true, GameObjectType::City);
	city->AddComponent(pPhysics);

	city->Initialize();

	return city;
}

GameObject* Factory::CreateMissile(Hash hash, exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition, exColor color, bool collisionActive, GameObjectType type)
{
	exColor missileColor = color;
	
	GameObject* missile = new GameObject(hash);

	COGTransform* pTransform = new COGTransform(missile, startPosition);
	missile->AddComponent(pTransform);

	COGMissileController* pMissileController = new COGMissileController(missile, pTransform, pEngine);
	pMissileController->SetVectorToMissile(finalPosition);
	missile->AddComponent(pMissileController);

	COGLineShape* pLineShape = new COGLineShape(pEngine, missile, startPosition, missileColor);
	missile->AddComponent(pLineShape);

	COGPhysics* pPhysics = new COGPhysics(missile, collisionActive, type);
	missile->AddComponent(pPhysics);

	missile->Initialize();

	return missile;
}

GameObject* Factory::CreateGameObject(exEngineInterface* pEngine, exVector2 startPosition, GameObjectType gameType)
{
	GameObject* newGameObject;
	++mIdentify;
	switch (gameType)
	{
	case GameObjectType::City:
	{
		++mCities;
		return newGameObject = CreateCity(s_hash("City" + std::to_string(mIdentify)), pEngine, startPosition);
	}
	case GameObjectType::Explosion:
		return newGameObject = CreateExplosion(s_hash("Explosion" + std::to_string(mIdentify)), pEngine, startPosition);
	default:
		std::cout << "Wrong type" << std::endl;
		return nullptr;
	}
}

GameObject* Factory::CreateMissiles(exEngineInterface* pEngine, exVector2 startPosition, exVector2 finalPosition, GameObjectType gameType) 
{
	GameObject* newGameObject;
	++mIdentify;
	switch (gameType)
	{
	case GameObjectType::MissileFriend:
	{
		--Factory::mMissiliesAvailable;
		exColor friendColor;
		friendColor.SetColor(255, 255, 255, 255);
		return newGameObject = CreateMissile(s_hash("Missile" + std::to_string(mIdentify)), pEngine, startPosition, finalPosition, friendColor, false, GameObjectType::MissileFriend);
	}
	case GameObjectType::MissileEnemy:
	{
		exColor enemyColor;
		enemyColor.SetColor(200, 0, 20, 255);
		return newGameObject = CreateMissile(s_hash("MissileEnemy" + std::to_string(mIdentify)), pEngine, startPosition, finalPosition, enemyColor, true, GameObjectType::MissileEnemy);
	}
	default:
		std::cout << "Wrong type" << std::endl;
		return nullptr;
	}
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