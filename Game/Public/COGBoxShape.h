#pragma once
#include "Game\Public\COGShape.h"
#include "Game\Public\COGTransform.h"

class COGBoxShape : public COGShape
{
public:

	COGBoxShape(exEngineInterface* pEngine, GameObject* pGO, float fWidth, float fHeight, exColor boxColor)
		:COGShape(pGO)
		, mWidth(fWidth)
		, mHeight(fHeight)
	{
		mEngine = pEngine;
		mTransform = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		mColor = boxColor;	
		mVertex1 = { 0.0f, 0.0f };
		mVertex2 = { 0.0f, 0.0f };
	}

	virtual ComponentType GetType() const { return ComponentType::BoxShape; }

	virtual exVector2 GetVertex1()
	{
		mVertex1 = mTransform->GetPosition();
		return mVertex1;
	}

	virtual exVector2 GetVertex2()
	{
		mVertex2 = { mVertex1.x + mWidth, mVertex1.y + mHeight };
		return mVertex2;
	}

	virtual void Render() override
	{
		 mEngine->DrawBox(GetVertex1(), GetVertex2(), mColor, 2);
	}

private:

	COGTransform*			mTransform;
	exVector2				mVertex1;
	exVector2				mVertex2;
	float					mWidth;
	float					mHeight;

};