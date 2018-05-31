#include "Game\Public\GameObject.h"
#include "Game\Public\GameObjectInventory.h"

GameObject::GameObject(Hash hash)
{
	mHash = hash;
	GameObjectInventory::Instance()->Register(this);
}

GameObject::~GameObject()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
}

void GameObject::Initialize() 
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}

GameObjectHandle GameObject::GetHandle()
{
	GameObjectHandle temp;
	temp.SetHash(mHash);
	return temp;
}