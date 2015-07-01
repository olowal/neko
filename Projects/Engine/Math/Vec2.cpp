//	Vec2.cpp

#include "Vec2.h"
#include "Engine/Math/Mat3x2.h"

namespace neko
{

Vec2 Vec2::Zero		= Vec2(0.0f, 0.0f);
Vec2 Vec2::Up		= Vec2(1.0f, 0.0f);
Vec2 Vec2::Right	= Vec2(0.0f, 1.0f);

Vec2 Vec2::operator*(const Mat3x2& mM) const
{
	Vec2 vV;
	vV.m_fX = (m_fX * mM._11) + (m_fY * mM._21) + mM._31;
	vV.m_fY = (m_fX * mM._12) + (m_fY * mM._22) + mM._32;
	return vV;
}

}	//	namespace neko