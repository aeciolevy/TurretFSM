#include "Game\Public\ScoreManager.h"
#include "Game/Public/Factory.h"
#include <string>

//Initializing static member outside of the constructor
ScoreManager* Singleton<ScoreManager>::mSingleton = nullptr;

int ScoreManager::score = 0;

void ScoreManager::Initialize(exEngineInterface* engine)
{
	mEngine = engine;
	mFontID = mEngine->LoadFont("PressStart2P.ttf", 18);
	mTextP2 = { ((kViewPortWidth / 2.0f) + 180.0f), 25.0f };
	mScorePositionP2 = { ((kViewPortWidth / 2.0f) + 350.0f), 25.0f };
	mMissileText = { ((kViewPortWidth / 2.0f) + 180.0f), 50.0f };
	mMissileText2 = { ((kViewPortWidth / 2.0f) + 350.0f), 50.0f };
	mTextColor.SetColor(255, 255, 255, 255);
}

void ScoreManager::RenderText()
{
	std::string p2Score(std::to_string(ScoreManager::score));
	const char* p2ScoreChar = p2Score.c_str();
	mEngine->DrawText(mFontID, mTextP2, "Score: ", mTextColor, 0);
	mEngine->DrawText(mFontID, mScorePositionP2, p2ScoreChar, mTextColor, 0);
}

void ScoreManager::RenderMissile()
{
	std::string missile(std::to_string(Factory::mMissiliesAvailable));
	const char* missileChar = missile.c_str();
	mEngine->DrawText(mFontID, mMissileText, "Missiles:", mTextColor, 0);
	mEngine->DrawText(mFontID, mMissileText2, missileChar, mTextColor, 0);
}

void ScoreManager::Render()
{
	RenderText();
	RenderMissile();
}