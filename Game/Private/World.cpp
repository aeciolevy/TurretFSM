#include "Game\Public\World.h"
#include "Game\Public\Factory.h"
#include "Engine/Public/SDL.h"
#include "Game\Public\Help.h"
#include "Game\Public\COGInput.h"
#include "Game\Public\COGController.h"
#include "Game\Public\COGFSM.h"

extern std::hash<std::string> s_hash;

World::World(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mFactory = Factory::Instance();
	mEnemy = new Enemy(pEngine);
	mUI = new UIManager(pEngine);
}

void World::Initialize()
{
	mFactory->CreateGameObject(mEngine, {0.0f, 250.0f}, GameObjectType::Turret);
}

void World::Destroy()
{
}

void World::DrawGameOver()
{
	int FontID = mEngine->LoadFont("PressStart2P.ttf", 20);
	exVector2 gameOverTextPos = { (kViewPortWidth / 2.0f), (kViewPortHeight / 2.0f)  };
	exColor TextColor;
	TextColor.SetColor(255, 255, 255, 255);
	mEngine->DrawText(FontID, gameOverTextPos, "Game Over", TextColor, 1);
}

void World::Update(float fDeltaT)
{
		if (ScoreManager::isDone)
		{
			mUI->GameOver();
		}
		else
		{
			mEnemy->Update(fDeltaT);
			for (COGMissileController* pMissileController : COGMissileController::mMissileControllerComponents)
			{
				pMissileController->Update(fDeltaT);
			}

			for (COGExplosionController* pExplosionController : COGExplosionController::mExplosionControllerComponents)
			{
				pExplosionController->Update(fDeltaT);
			}

			for (COGFSM* pFSM : COGFSM::mFSMComponents)
			{
				pFSM->Update(fDeltaT);
			}

			for (COGController* pController : COGController::mControllerComponents)
			{
				pController->Update(fDeltaT);
			}

			for (COGInput* pInput : COGInput::mInputComponents)
			{
				pInput->Update();
			}

			// run simulation first
			for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
			{
				pPhysics->Update(fDeltaT);
			}

			// then render everything
			for (COGShape* pShape : COGShape::mShapeComponents)
			{
				pShape->Render();
			}
			mUI->Render(fDeltaT);
			mFactory->cleanStaleList();
		}
}