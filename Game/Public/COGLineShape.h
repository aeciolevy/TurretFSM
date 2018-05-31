#pragma once
#pragma once
#include "Game\Public\COGShape.h"
#include "Game\Public\COGTransform.h"

class COGLineShape : public COGShape
{
public:

	COGLineShape(exEngineInterface* pEngine, GameObject* pGO, exVector2 startPosition, exColor missileColor)
		:COGShape(pGO)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mStartPos = mTransform->GetPosition();
		mColor = missileColor;
	}

	virtual ComponentType GetType() const { return ComponentType::LineShape; }

	virtual exVector2 GetPosition()
	{
		return mTransform->GetFinalPos();
	}

	virtual void Render() override
	{
		mFinalPos = mTransform->GetFinalPos();
		mEngine->DrawLine(mStartPos, mFinalPos, mColor, 2);
	}

private:

	COGTransform *			mTransform;
	exVector2				mStartPos;
	exVector2				mFinalPos;
	exColor					mColor;
	

};