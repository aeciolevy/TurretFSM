//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Pong with Components";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mWorld( nullptr )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	mScoreManager = ScoreManager::Instance();
	mScoreManager->Initialize(mEngine);

	mWorld = new World(mEngine);
	mWorld->Initialize();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

void MyGame::DrawCrosshair()
{
	exVector2 p1, p2;
	exColor c;
	c.mColor[0] = 255;
	c.mColor[1] = 255;
	c.mColor[2] = 255;
	p1.x = mMousePosition.x - 10.0f;
	p1.y = mMousePosition.y - 10.0f;
	p2.x = mMousePosition.x + 10.0f;
	p2.y = mMousePosition.y + 10.0f;
	mEngine->DrawLineBox(p1, p2, c, 1);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int x, y;
	unsigned int r = SDL_GetMouseState(&x, &y);

	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	DrawCrosshair();
	mWorld->Update(fDeltaT);
	mScoreManager->Render();
}
