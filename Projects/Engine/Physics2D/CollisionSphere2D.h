/****************************************************************************
//	Filename: CollisionSphere2D.h
//	Description: A 2D sphere used only for visibility testing.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Vec2.h"

namespace neko
{

class CollisionSphere2D
{
public:
	CollisionSphere2D(){}
	~CollisionSphere2D(){}

	void SetPosition(const Vec2& vPos){ m_vPos = vPos; }
	void SetPosition(float fX, float fY) { m_vPos.m_fX = fX; m_vPos.m_fY = fY;}

	const Vec2& GetPosition() const { return m_vPos; }

	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	float GetRadius() const { return m_fRadius; }

private:
	Vec2 m_vPos;
	float m_fRadius;
};

}	//	namespace neko