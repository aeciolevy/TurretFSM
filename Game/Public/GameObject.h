#pragma once

#include <vector>
#include <algorithm>
#include "Engine/Public/EngineTypes.h"
#include "Game\Public\GameObjectHandle.h"

typedef unsigned int Hash;
class GameObjectHandle;
class GameObject;

// all the different types of components
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	LineShape,
	Bounce, 
	Controller,
	Explosion,
	ExplosionController,
	MissileController
};

enum class PaddleIdentifier : int
{
	PaddleLeft = 0,
	PaddleRight,
};

class Component
{
public:

	Component(GameObject* pGO);
	virtual ComponentType GetType() const = 0;
	virtual void Initialize() { }
	virtual void Destroy() { }

protected:

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.erase(std::remove(componentVector.begin(), componentVector.end(), this), componentVector.end());
	}
	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

protected:

	GameObject * mGO;

};

class GameObject
{
public:
	Hash	mHash;
public:

	GameObject(Hash hash);
	~GameObject();
	void Initialize();
	void AddComponent(Component* pComponent);
	
	GameObjectHandle GetHandle();

	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}
		return nullptr;
	}

private:
	
	std::vector<Component*>		mComponents;
};

