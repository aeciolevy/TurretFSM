#pragma once
#pragma once
#include "Game\Public\COGShape.h"
#include "Game\Public\COGTransform.h"
#include "Game\Public\Help.h"
#include "Game\Public\Output.h"

class COGLineShape : public COGShape
{
public:

	COGLineShape(exEngineInterface* pEngine, GameObject* pGO, exVector2 startPosition, exColor lineColor)
		:COGShape(pGO)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mStartPos = startPosition;
		mFinalPos = { startPosition.x + 30.0f, startPosition.y + 30.0f };
		mColor = lineColor;
	}

	virtual ComponentType GetType() const { return ComponentType::LineShape; }

	virtual void SetFinalPos()
	{
		exVector2 temp;
		mMousePosition = Help::GetMousePosition();
		temp = mMousePosition.Sub(mStartPos);
		temp = temp.Normalize();
		temp = temp.MultVectorByFactor(30.0f);
		temp.x = temp.Clamp(temp.x, 0, 100);
		temp.y = temp.Clamp(temp.y, -30, 30);
		mFinalPos = mStartPos.Add(temp);
	}

	virtual exVector2 GetPosition()
	{
		return mTransform->GetFinalPos();
	}

	virtual void Render() override
	{
		SetFinalPos();
		mEngine->DrawLine(mStartPos, mFinalPos, mColor, 2);
	}

private:

	COGTransform *			mTransform;
	exVector2				mStartPos;
	exVector2				mFinalPos;
	exColor					mColor;
	exVector2				mMousePosition;

};