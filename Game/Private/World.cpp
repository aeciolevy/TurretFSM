#include "Game\Public\World.h"
#include "Game\Public\Factory.h"
#include "Engine/Public/SDL.h"
#include "Game\Public\Help.h"

extern std::hash<std::string> s_hash;

World::World(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mMouseLeft = 0;
	mFactory = Factory::Instance();
}

void World::Initialize()
{

	GameObject* city =mFactory->CreateGameObject(mEngine, {0.0f, 250.0f}, GameObjectType::Turret);
}

void World::MouseClick()
{
	int x, y;
	unsigned int r = SDL_GetMouseState(&x, &y);

	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;

	mMouseLeft = r & SDL_BUTTON(SDL_BUTTON_LEFT);
}

void World::LauchMissile()
{


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
		MouseClick();

		for (COGMissileController* pMissileController : COGMissileController::mMissileControllerComponents)
		{
			pMissileController->Update(fDeltaT);
		}

		for (COGExplosionController* pExplosionController : COGExplosionController::mExplosionControllerComponents)
		{
			pExplosionController->Update(fDeltaT);
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

		
}