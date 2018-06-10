#pragma once
#include "Engine\Public\EngineTypes.h"
#include "Engine\Public\EngineInterface.h"

class UIManager
{
public:
	UIManager(exEngineInterface* pEngine);

	void RenderScore();
	void RenderHealth();
	void RenderBullet();
	void RenderWeapon();
	void StartMessage(float deltaTIme);
	void GameOver();

	void Render(float deltaTime);

private:
	exEngineInterface * mEngine;
	int					mFontID;
	exColor				mTextColor;
	exVector2			mTextP2;
	exVector2			mScorePositionP2;
	exVector2			mMissileText;
	exVector2			mMissileText2;
	float				mFlashMessage;
};
