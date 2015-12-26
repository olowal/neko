/****************************************************************************
//	Filename: CollisionDetection.h
//	Description: Helper functions for detecting collision
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Physics2D/CollisionShape.h"
namespace neko
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

inline bool CircleToCircle(const CircleShape2D& a, const CircleShape2D& b)
{
	return ((a.GetPosition().Distance(b.GetPosition())) < (a.shape.radius + b.shape.radius));
}

inline bool CircleToBox(const CircleShape2D& circle, const BoxShape2D& box)
{
	return false;
}
}	//	namespace neko
