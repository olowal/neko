/****************************************************************************
//	Filename: CollisionDetection.h
//	Description: Helper functions for detecting collision
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Physics2D/CollisionShape.h"
#include "Engine/Math/Utils.h"
namespace neko
{
namespace collision
{
inline bool PointInBox(const BoxShape2D& box, const Vec2& point)
{
	const Vec2 pos = box.GetPosition();
	const Vec2 extents = box.shape.extents;

	if(point.m_fX < pos.m_fX) { return false; }
	if(point.m_fX > pos.m_fX + extents.m_fX) { return false; }
	if(point.m_fY < pos.m_fY) { return false; }
	if(point.m_fY > pos.m_fY + extents.m_fY) { return false; }

	return true;
}

inline bool PointInCircle(const CircleShape2D& circle, const Vec2& point)
{
	return point.Distance(circle.GetPosition()) < circle.shape.radius;
}

inline bool CircleToCircle(const CircleShape2D& a, const CircleShape2D& b)
{
	return ((a.GetPosition().Distance(b.GetPosition())) < (a.shape.radius + b.shape.radius));
}

inline bool CircleToBox(const CircleShape2D& circle, const BoxShape2D& box)
{
	const Vec2 circlePos = circle.GetPosition();
	const Vec2 boxPos = box.GetPosition();
	const Vec2 boxExtents = box.shape.extents;

	const float boxLeft = boxPos.m_fX;
	const float boxRight = boxPos.m_fX + boxExtents.m_fX;
	const float boxTop = boxPos.m_fY;
	const float boxBottom = boxPos.m_fY + boxExtents.m_fY;

	const float closestX = math::Clamp(circlePos.m_fX, boxLeft, boxRight);
	const float closestY = math::Clamp(circlePos.m_fY, boxBottom, boxTop);

	const float distanceX = circlePos.m_fX - closestX;
	const float distanceY = circlePos.m_fY - closestY;

	const float distanceSq = (distanceX * distanceX) + (distanceY * distanceX);

	return distanceSq < (circle.shape.radius * circle.shape.radius);
}

inline bool BoxToBox(const BoxShape2D& a, const BoxShape2D& b)
{
	const Vec2 aPos = a.GetPosition();
	const Vec2 bPos = b.GetPosition();
	
	const Vec2 aExt = a.shape.extents;
	const Vec2 bExt = b.shape.extents;

	if((aPos.m_fX + aExt.m_fX) < bPos.m_fX) { return false; }
	if(aPos.m_fX > (bPos.m_fX + bExt.m_fX)) { return false; }
	if((aPos.m_fY + aExt.m_fY) < bPos.m_fY) { return false; }
	if(aPos.m_fY > (bPos.m_fY + bExt.m_fY)) { return false; }

	return true;
}
}	//	namespace collision
}	//	namespace neko
