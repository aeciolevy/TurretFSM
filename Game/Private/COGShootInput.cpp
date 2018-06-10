#include "Game\Public\COGShootInput.h"
#include "Game\Public\Factory.h"

void COGShootInput::ChangeState()
{
	if (Help::SpacePressed() && !mSpacePressed)
	{
		if (mFSM->mState == State::Normal)
		{
			mFSM->Next(new FSMNormalBullet(mFSM), State::BigShoot);
			ScoreManager::weapon = "Big";
		}
		else
		{
			mFSM->Next(new FSMNormalBullet(mFSM), State::Normal);
			ScoreManager::weapon = "Small";
		}
	}
	mSpacePressed = Help::SpacePressed();
}

void COGShootInput::Update()
{
	if (Help::MouseClicked() && !mMouseClick)
	{
		--ScoreManager::bullets;
		mPosition = mTransform->GetFinalPos();
		if (mFSM->mState == State::Normal)
		{
			Factory::Instance()->CreateGameObject(mEngine, mPosition, GameObjectType::Bullet);
		}
		else if (mFSM->mState == State::BigShoot)
		{
			Factory::Instance()->CreateGameObject(mEngine, mPosition, GameObjectType::BigBullet);
		}
	}
	mMouseClick = Help::MouseClicked();
	ChangeState();
}