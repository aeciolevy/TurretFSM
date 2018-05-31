#pragma once
#include "Game\Public\GameObject.h"
#include "Engine\Public\EngineInterface.h"
// COGShape - our baseclass for shapes
class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

public:

	COGShape(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual void Initialize() override
	{
		AddToComponentVector(mShapeComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mShapeComponents);
	}

	virtual void Render() = 0;

protected:

	exEngineInterface *			mEngine;
	exColor						mColor;
};
