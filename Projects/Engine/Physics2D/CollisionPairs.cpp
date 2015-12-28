//	CollisionPairs.cpp
#include "CollisionPairs.h"
#include "Engine/Physics2D/CollisionDetection.h"

namespace neko
{

template <>
bool CircleToCircleCollision2D::Intersects() const
{
	return collision::CircleToCircle(a, b);
}

template <>
bool CircleToBoxCollision2D::Intersects() const
{
	return collision::CircleToBox(a, b);
}

template <>
bool BoxToCircleCollision2D::Intersects() const
{
	return collision::CircleToBox(b, a);
}

template <>
bool BoxToBoxCollision2D::Intersects() const
{
	return collision::BoxToBox(a, b);
}
}	//	namespace neko
