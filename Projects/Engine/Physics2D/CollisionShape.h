/****************************************************************************
//	Filename: CollisionShape.h
//	Description: CollisionShape
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Vec2.h"
namespace neko
{

class CircleShape;
class CollisionShape
{
public:
	CollisionShape(){}
	virtual ~CollisionShape(){}

	virtual bool Intersects(const CircleShape* pShape){return false;}

	void SetPosition(const Vec2& vPos) { m_vPos = vPos; }
	const Vec2& GetPosition() const { return m_vPos; }

protected:
	Vec2 m_vPos;
};

}	//	namespace neko