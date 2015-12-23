/****************************************************************************
//	Filename: CircleShape.h
//	Description: Representation of a 2D circle used for collision purpose.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Physics2D/CollisionShape.h"
namespace neko
{

class CircleShape : public CollisionShape
{
public:

	bool Intersects(const CircleShape* pCircle)
	{
		const Vec2 vA = m_vPos;
		const Vec2 vB = pCircle->GetPosition();
		const float fDistanceSq = (vA - vB).AbsSquare();
		const float fA = m_fRad;
		const float fB = pCircle->GetRadius();

		if(fDistanceSq < ((fA * fA) + (fB * fB)))
		{
			return true;
		}

		return false;
	}

	float GetRadius() const { return m_fRad; }
	void SetRadius(float fRad) { m_fRad = fRad; }

private:
	float m_fRad;
};

}	//	namespace neko
