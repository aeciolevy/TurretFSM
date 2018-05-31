#pragma once
#include "Game/Public/HashMap.h"
#include "Game/Public/Singleton.h"

class GameObject;

class GameObjectInventory : public Singleton<GameObjectInventory>
{
public:
	friend class Singleton<GameObjectInventory>;

	void Register(GameObject* pGO)
	{
		mMap.InsertNoCheck(pGO);
	}

	void Unregister(GameObject* pGO)
	{
		mMap.Delete(pGO);
	}

	bool Exists(Hash hash) const
	{
		return (mMap.Find(hash) != nullptr);
	}

	GameObject* Lookup(Hash hash)
	{
		return mMap.Find(hash);
	}

	const GameObject* Lookup(Hash hash) const
	{
		return mMap.Find(hash);
	}

private:
	HashMap<GameObject*, 256> mMap;
}; 

GameObjectInventory* Singleton<GameObjectInventory>::mSingleton = nullptr;