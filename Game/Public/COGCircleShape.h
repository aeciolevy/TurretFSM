#pragma once
#include "Game\Public\COGShape.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\ScoreManager.h"
#include "Game\Public\Output.h"

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(exEngineInterface* pEngine, GameObject* pGO, float fRadius, exColor color)
		: COGShape(pGO)
		, mRadius(fRadius)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mColor = color;
	}

	virtual ComponentType GetType() const { return ComponentType::CircleShape; }

	virtual float GetRadius()
	{
		return mRadius;
	}

	virtual exVector2 GetCenter()
	{
		return mTransform->GetPosition();
	}

	virtual void Render() override
	{
		mCenter = mTransform->GetPosition();
		mEngine->DrawCircle(mCenter, mRadius, mColor, 2);
	}

private:

	float					mRadius;
	exVector2				mCenter;
	COGTransform*			mTransform;
};
