#pragma once
#include "Game\Public\COGShape.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\ScoreManager.h"
#include "Game\Public\Output.h"

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(exEngineInterface* pEngine, GameObject* pGO, float fRadius)
		: COGShape(pGO)
		, mRadius(fRadius)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mColor.mColor[0] = 255;
		mColor.mColor[1] = 255;
		mColor.mColor[2] = 255;
		mColor.mColor[3] = 255;
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

	virtual void CheckScore()
	{
		float xPositionLeft = mTransform->GetPosition().x - mRadius;
		float xPositionRight = mTransform->GetPosition().x + mRadius;
		if (xPositionLeft <= 0)
		{
			mTransform->ResetPosition({ 550.0f, 300.0f});
		}
		if (xPositionRight >= kViewPortWidth)
		{
			mTransform->ResetPosition({ 350.0f, 300.0f });
		}
	}

	virtual void Render() override
	{
		CheckScore();
		mCenter = mTransform->GetPosition();
		mEngine->DrawCircle(mCenter, mRadius, mColor, 2);
	}

private:

	float					mRadius;
	exVector2				mCenter;
	COGTransform*			mTransform;
};
