#include "Game\Public\COGShootInput.h"
#include "Game\Public\Factory.h"
void COGShootInput::Update()
{
	if (Help::MouseClicked() && !mMouseClick)
	{
		exOutput("mouseClicked");
		// Instatiate a bullet
		mPosition = mTransform->GetFinalPos();
		Factory::Instance()->CreateGameObject(mEngine, mPosition, GameObjectType::Bullet);
	}
	mMouseClick = Help::MouseClicked();
}