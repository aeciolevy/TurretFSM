#pragma once

class Component
{
public:

	Component(GameObject* pGO)
		: mGO(pGO)
	{
	}

	virtual ComponentType GetType() const = 0;

	virtual void Initialize() { }
	virtual void Destroy() { }

protected:

	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.erase(std::remove(componentVector.begin(), componentVector.end(), this), componentVector.end());
	}

protected:

	GameObject * mGO;

};
