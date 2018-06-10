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
	mCircle = mGO->FindComponent<COGCircleShape>(ComponentType::CircleShape);
	mMissile = mGO->FindComponent<COGLineShape>(ComponentType::LineShape);
	AddToComponentVector(mPhysicsComponents);
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


CircleParams COGPhysics::GetCircleParams()
{
	CircleParams temp;
	temp.Radius = mCircle->GetRadius();
	temp.Center = mCircle->GetCenter();
	return temp;
}

BoxParams COGPhysics::GetBoxParams(COGBoxShape* boxShape)
{
	BoxParams temp;
	temp.vertex1 = boxShape->GetVertex1();
	temp.vertex2 = boxShape->GetVertex2();
	return temp;
}

float findNearestPoint(float Center, float TopLeft, float BottomRight)
{
	return std::max(TopLeft, std::min(Center, BottomRight));
}

exVector2 GetNearestVector(CircleParams Circle, BoxParams Box)
{
	float x = Circle.Center.x - findNearestPoint(Circle.Center.x, Box.vertex1.x, Box.vertex2.x);
	float y = Circle.Center.y - findNearestPoint(Circle.Center.y, Box.vertex1.y, Box.vertex2.y);
	return { x, y };
}
// Based on https://yal.cc/rectangle-circle-intersection-test/
bool IsCircleBoxColliding(CircleParams Circle, BoxParams Box)
{
	float DeltaX = GetNearestVector(Circle, Box).x;
	float DeltaY = GetNearestVector(Circle, Box).y;
	return (DeltaX * DeltaX + DeltaY * DeltaY) < (Circle.Radius * Circle.Radius);
}



//exVector2 COGPhysics::GetNormal(COGPhysics* pOther)
//{
//	CircleParams circle = GetCircleParams();
//	BoxParams box = GetBoxParams(pOther->mBoxShape);
//	float xPoint = GetNearestVector(circle, box).x;
//	float yPoint = GetNearestVector(circle, box).y;
//	exVector2 temp = { xPoint, yPoint };
//	return temp.Normalize();
//}


//bool isCollidingCircleAndLine(exVector2 circleCenter, float circleRadius, exVector2 linePosition)
//{
//	exVector2 vector = linePosition.GetVector(circleCenter);
//	float magnitude = vector.Magnitude();
//
//	if (magnitude <= circleRadius)
//	{
//		return true;
//	}
//	return false;
//}

bool isCollidingCircleAndCircle(exVector2 circleCenter, float circleRadius, exVector2 circleCenter2, float circleRadius2)
{
	exVector2 vector = circleCenter.GetVector(circleCenter2);
	float magnitude = vector.Magnitude();
	float maxRadius = std::max(circleRadius, circleRadius2);
	if (magnitude < maxRadius)
	{
		return true;
	}
	return false;
}

//bool isCollidingTurretAndCircle(exVector2 boxTopLeft, exVector2 boxBottomRight, exVector2 circleCenter, float radius)
//{
//	float xLimit = boxBottomRight.x;
//	float yLimit1 = boxTopLeft.y;
//	float yLimit2 = boxBottomRight.y;
//	float edgex = circleCenter.x - radius;
//	float edgey1 = circle;
//}


//bool isCollidingBoxAndLine(exVector2 boxTopLeft, exVector2 linePosition)
//{
//	float xMissile = linePosition.x;
//	float yMissile = linePosition.y;
//	float xCityLeft = boxTopLeft.x;
//	float xCityRight = boxTopLeft.x + CITY_WIDTH;
//	float yCity = boxTopLeft.y;
//	if (yCity <= yMissile && (xMissile > xCityLeft && xMissile < xCityRight))
//	{
//		return true;
//	}
//	return false;
//}

bool COGPhysics::IsColliding(COGPhysics* pOther)
{
	// Check collision between bullet and enemy
	if ((this->mType == GameObjectType::Bullet || this->mType == GameObjectType::BigBullet) && pOther->mType == GameObjectType::Enemy)
	{
		bool temp = isCollidingCircleAndCircle(this->mCircle->GetCenter(), this->mCircle->GetRadius(), pOther->mCircle->GetCenter(), pOther->mCircle->GetRadius());
		if (temp)
		{
			ScoreManager::score += 20;
			Factory::Instance()->addToStaleList(pOther->mGO);
			Factory::Instance()->addToStaleList(this->mGO);
		}
		return temp;
	}

	if (this->mType == GameObjectType::Enemy && pOther->mType == GameObjectType::Turret)
	{
		CircleParams circlePar = GetCircleParams();
		BoxParams boxParams = GetBoxParams(pOther->mBoxShape);
		bool temp = IsCircleBoxColliding(circlePar, boxParams);
		if (temp)
		{
			ScoreManager::health -= 25;
			Factory::Instance()->addToStaleList(this->mGO);
			// set game over to score manager
			if (ScoreManager::health <= 0)
			{			
				ScoreManager::isDone = true;
			}
		}
	}

	return false;
}




