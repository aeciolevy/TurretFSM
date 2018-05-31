#include "Game\Public\COGPhysics.h"
#include "Game\Public\COGBounce.h"
#include "Game/Public/Output.h"

const float CITY_WIDTH = 100.0f;
std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

COGPhysics::COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents, GameObjectType type)
	: Component(pGO)
	, mGenerateCollisionEvents(bGenerateCollisionEvents)
	
{
	mGO = pGO;
	mType = type;
}

void COGPhysics::Initialize() 
{
	mTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mBoxShape = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mExplosion = mGO->FindComponent<COGExplosion>(ComponentType::Explosion);
	mMissile = mGO->FindComponent<COGLineShape>(ComponentType::LineShape);
	AddToComponentVector(mPhysicsComponents);
	// If it is a ball add bounce to Event collision vector
	//if (mGenerateCollisionEvents)
	//{
	//	COGBounce* mBounce = mGO->FindComponent<COGBounce>(ComponentType::Bounce);
	//	// Upcast bounce to IPhysicsCollision event
	//	IPhysicsCollisionEvent* temp = dynamic_cast<COGBounce*>(mBounce);
	//	mCollisionEventListeners.push_back(temp);
	//}
}

COGPhysics::~COGPhysics()
{
	for (int i = 0; i < int(mCollisionEventListeners.size()); i++)
	{
		if (dynamic_cast<Component *>(mCollisionEventListeners[i]) == nullptr)
		{
			delete mCollisionEventListeners[i];
		}

		mCollisionEventListeners.erase(mCollisionEventListeners.begin() + i);
	}
}


void COGPhysics::Destroy()
{
	RemoveFromComponentVector(mPhysicsComponents);
}

void COGPhysics::Update(float fDeltaT)
{
	// check collisions
	if (mGenerateCollisionEvents)
	{
		for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
		{
			// do not collide with self
			if (pPhysicsOther == this)
			{
				continue;
			}

			const bool bResult = IsColliding(pPhysicsOther);

			if (bResult)
			{
				
				bool b = bResult;
				//exVector2 normal = GetNormal(pPhysicsOther);
				for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
				{
					pCollisionEventListener->OnCollision(this, pPhysicsOther);
				}
			}
		}
	}
}

exVector2& COGPhysics::GetVelocity()
{
	return mVelocity;
}

//void COGPhysics::SetVelocity(exVector2 newVelocity)
//{
//	mVelocity = newVelocity;
//}

//CircleParams COGPhysics::GetCircleParams()
//{
//	CircleParams temp;
//	temp.Radius = mCircleShape->GetRadius();
//	temp.Center = mCircleShape->GetCenter();
//	return temp;
//}

//BoxParams COGPhysics::GetBoxParams(COGBoxShape* boxShape)
//{
//	BoxParams temp;
//	temp.vertex1 = boxShape->GetVertex1();
//	temp.vertex2 = boxShape->GetVertex2();
//	return temp;
//}

//float findNearestPoint(float Center, float TopLeft, float BottomRight)
//{
//	return std::max(TopLeft, std::min(Center, BottomRight));
//}
//
//exVector2 GetNearestVector(CircleParams Circle, BoxParams Box)
//{
//	float x = Circle.Center.x - findNearestPoint(Circle.Center.x, Box.vertex1.x, Box.vertex2.x);
//	float y = Circle.Center.y - findNearestPoint(Circle.Center.y, Box.vertex1.y, Box.vertex2.y);
//	return { x, y };
//}
//// Based on https://yal.cc/rectangle-circle-intersection-test/
//bool IsCircleBoxColliding(CircleParams Circle, BoxParams Box)
//{
//	float DeltaX = GetNearestVector(Circle, Box).x;
//	float DeltaY = GetNearestVector(Circle, Box).y;
//	return (DeltaX * DeltaX + DeltaY * DeltaY) < (Circle.Radius * Circle.Radius);
//}



//exVector2 COGPhysics::GetNormal(COGPhysics* pOther)
//{
//	CircleParams circle = GetCircleParams();
//	BoxParams box = GetBoxParams(pOther->mBoxShape);
//	float xPoint = GetNearestVector(circle, box).x;
//	float yPoint = GetNearestVector(circle, box).y;
//	exVector2 temp = { xPoint, yPoint };
//	return temp.Normalize();
//}


bool isCollidingCircleAndLine(exVector2 circleCenter, float circleRadius, exVector2 linePosition)
{
	exVector2 vector = linePosition.GetVector(circleCenter);
	float magnitude = vector.Magnitude();
	if (magnitude <= circleRadius)
	{
		return true;
	}
	return false;
}

bool isCollidingBoxAndLine(exVector2 boxTopLeft, exVector2 linePosition)
{
	float xMissile = linePosition.x;
	float yMissile = linePosition.y;
	float xCityLeft = boxTopLeft.x;
	float xCityRight = boxTopLeft.x + CITY_WIDTH;
	float yCity = boxTopLeft.y;
	if (yCity <= yMissile && (xMissile > xCityLeft && xMissile < xCityRight))
	{
		return true;
	}
	return false;
}
bool COGPhysics::IsColliding(COGPhysics* pOther)
{
	/*if (this->mExplosion != nullptr && this->mGenerateCollisionEvents && pOther->mMissile != nullptr && pOther->mGenerateCollisionEvents)
	{
		
	}*/

	if (this->mType == GameObjectType::Explosion && pOther->mType == GameObjectType::MissileEnemy)
	{
		bool temp = isCollidingCircleAndLine(this->mExplosion->GetCenter(), this->mExplosion->GetRadius(), pOther->mMissile->GetPosition());
		if (temp)
		{
			ScoreManager::score += 10;
			Factory::Instance()->addToStaleList(pOther->mGO);
		}
		return temp;
	}

	if (this->mType == GameObjectType::City && pOther->mType == GameObjectType::MissileEnemy)
	{
		bool temp = isCollidingBoxAndLine(this->mTransform->GetPosition(), pOther->mTransform->GetFinalPos());
		if (temp)
		{
			Factory::Instance()->addToStaleList(this->mGO);
			return true;
		}
	}
	//// we don't cover the other cases
	//// maybe assert here?

	return false;
}




