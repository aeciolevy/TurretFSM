#pragma once
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineTypes.h"
#include "Engine\Public\EngineInterface.h"
class ScoreManager : public Singleton<ScoreManager>
{
public:
	friend class Singleton<ScoreManager>;
	void Initialize(exEngineInterface* engine);
	void Render();
	void RenderText();
	void RenderMissile();
	static int score;
private:
	exEngineInterface * mEngine;
	int					mFontID;
	exColor				mTextColor;
	exVector2			mTextP2;
	exVector2			mScorePositionP2;
	exVector2			mMissileText;
	exVector2			mMissileText2;
};