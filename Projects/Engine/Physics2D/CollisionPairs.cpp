//	CollisionPairs.cpp
#include "CollisionPairs.h"

namespace neko
{
template <>
bool CircleToCircleCollision2D::Intersects() const
{
	return ((a.GetPosition().Distance(b.GetPosition())) < (a.shape.radius + b.shape.radius));
}
template <>
bool CircleToBoxCollision2D::Intersects() const
{
	const float radius = a.shape.radius;
	Vec2 max(radius, radius);
	Vec2 min;
	return true;
}
}	//	namespace neko
