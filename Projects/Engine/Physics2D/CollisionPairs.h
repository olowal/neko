/****************************************************************************
//	Filename: CollisionPairs.h
//	Description: Combination of shapes, helper functions etc
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Physics2D/CollisionShape.h"
namespace neko
{

template <class ShapeA, class ShapeB>
class CollisionPair
{
public:
	ShapeA a;
	ShapeB b;

	bool Intersects() const;
};

typedef CollisionPair<CircleShape2D, CircleShape2D> CircleToCircleCollision2D;
typedef CollisionPair<BoxShape2D, CircleShape2D> BoxToCircleCollision2D;
typedef CollisionPair<CircleShape2D, BoxShape2D> CircleToBoxCollision2D;
typedef CollisionPair<BoxShape2D, BoxShape2D> BoxToBoxCollision2D;

}	//	namespace neko
