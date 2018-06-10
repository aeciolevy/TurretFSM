#include "Game/Public/UIManager.h"
#include "Game/Public/Factory.h"
#include <string>

UIManager::UIManager(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mFontID = mEngine->LoadFont("PressStart2P.ttf", 18);
	mTextP2 = { ((kViewPortWidth / 2.0f) + 180.0f), 25.0f };
	mScorePositionP2 = { ((kViewPortWidth / 2.0f) + 330.0f), 25.0f };
	mTextColor.SetColor(255, 255, 255, 255);
	mFlashMessage = 4.0f;
}

void UIManager::RenderScore()
{
	std::string p2Score(std::to_string(ScoreManager::score));
	const char* p2ScoreChar = p2Score.c_str();
	mEngine->DrawText(mFontID, mTextP2, "Score: ", mTextColor, 0);
	mEngine->DrawText(mFontID, mScorePositionP2, p2ScoreChar, mTextColor, 0);
}

void UIManager::RenderHealth()
{
	exVector2 text = { ((kViewPortWidth / 2.0f) + 180.0f), 50.0f };
	exVector2 healthPos = { ((kViewPortWidth / 2.0f) + 330.0f), 50.0f };
	std::string p2health(std::to_string(ScoreManager::health));
	const char* p2HealthChar = p2health.c_str();
	mEngine->DrawText(mFontID, text, "Health: ", mTextColor, 0);
	mEngine->DrawText(mFontID, healthPos, p2HealthChar, mTextColor, 0);
}

void UIManager::RenderBullet()
{
	exVector2 text = { (kViewPortWidthMin + 20.0f), 25.0f };
	exVector2 bulletPos = { (kViewPortWidthMin + 180.0f), 25.0f };
	std::string p2bullet(std::to_string(ScoreManager::bullets));
	const char* p2BulletChar = p2bullet.c_str();
	mEngine->DrawText(mFontID, text, "Bullets: ", mTextColor, 0);
	mEngine->DrawText(mFontID, bulletPos, p2BulletChar, mTextColor, 0);
}

void UIManager::RenderWeapon()
{
	exVector2 text = { (kViewPortWidthMin + 20.0f), 50.0f };
	exVector2 weaponPos = { (kViewPortWidthMin + 180.0f), 50.0f };
	const char* p2WeaponChar = ScoreManager::weapon.c_str();
	mEngine->DrawText(mFontID, text, "Weapon:", mTextColor, 0);
	mEngine->DrawText(mFontID, weaponPos, p2WeaponChar, mTextColor, 0);
}

void UIManager::StartMessage(float deltaTime)
{
	mFlashMessage -= deltaTime;
	if (mFlashMessage > 0)
	{
		exVector2 text = { ( (kViewPortWidth / 2) - 200.0f), (kViewPortHeight / 2) };
		mEngine->DrawText(mFontID, text, "Press space to switch weapon", mTextColor, 0);
	}
}

void UIManager::GameOver()
{
	exVector2 gameOverTextPos = { (kViewPortWidth / 2.0f), (kViewPortHeight / 2.0f) };
	exColor TextColor;
	TextColor.SetColor(220, 5, 5, 255);
	mEngine->DrawText(mFontID, gameOverTextPos, "Game Over", TextColor, 1);
}

void UIManager::Render(float deltaTime)
{
	RenderScore();
	RenderHealth();
	RenderBullet();
	RenderWeapon();
	StartMessage(deltaTime);
}