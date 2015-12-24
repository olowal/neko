/****************************************************************************
//	Filename: Vec2.h
//	Description: A Vector2 class and math functions.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
typedef struct lua_State lua_State;
namespace neko
{

class Mat3x2;
class Vec2
{
public:
	float m_fX, m_fY;
	
	Vec2()
	{
		m_fX = m_fY = 0.0f;
	}

	Vec2(float p_fX, float p_fY)
	{
		m_fX = p_fX;
		m_fY = p_fY;
	}

	Vec2(const Vec2& p_xV)
	{
		m_fX = p_xV.m_fX;
		m_fY = p_xV.m_fY;
	}

	Vec2& operator=(const Vec2& p_vV)
	{
		m_fX = p_vV.m_fX;
		m_fY = p_vV.m_fY;
		return *this;
	}

	void Clear() { (*(int*)&m_fX) = (*(int*)&m_fY) = 0; };
	void SetXY(float p_fX, float p_fY, float p_fZ) { m_fX = p_fX; m_fY = p_fY; }

	Vec2 operator+(const Vec2& p_kxrA) const { return Vec2(m_fX + p_kxrA.m_fX, m_fY + p_kxrA.m_fY); }
	Vec2& operator+=(const Vec2& p_kxrA) { m_fX += p_kxrA.m_fX; m_fY += p_kxrA.m_fY; return *this; }
	Vec2 operator-(const Vec2& p_kxrA) const { return Vec2(m_fX - p_kxrA.m_fX, m_fY - p_kxrA.m_fY); }
	Vec2& operator-=(const Vec2& p_kxrA) { m_fX -= p_kxrA.m_fX; m_fY -= p_kxrA.m_fY; return *this; }

	Vec2 operator-()const { return Vec2(-m_fX, -m_fY); }

	Vec2 operator*(float p_fF) const { return Vec2(m_fX*p_fF, m_fY*p_fF); }
	Vec2& operator*=(float p_fF) { m_fX *= p_fF; m_fY *= p_fF; return *this; }
	Vec2 operator/(float p_fF) const { return Vec2(m_fX / p_fF, m_fY / p_fF); }
	Vec2& operator/=(float p_fF) { m_fX /= p_fF; m_fY /= p_fF; return *this; }

	Vec2 operator*(const Mat3x2& mM) const;

	float operator*(const Vec2& p_kxrA) const { return m_fX*p_kxrA.m_fX + m_fY*p_kxrA.m_fY; }

	bool operator==(const Vec2& p_kxrA)	const { return m_fX == p_kxrA.m_fX&&m_fY == p_kxrA.m_fY; };
	bool operator!=(const Vec2& p_kxrA)	const { return m_fX != p_kxrA.m_fX || m_fY != p_kxrA.m_fY; };

	float Dot(const Vec2& p_kxrV) const { return m_fX*p_kxrV.m_fX + m_fY*p_kxrV.m_fY; };

	float Abs() const { return (sqrtf(m_fX*m_fX + m_fY*m_fY)); }
	float AbsSquare() const { return (m_fX*m_fX + m_fY*m_fY); }
	float AbsM() const { return ((float)fabs(m_fX)) + ((float)fabs(m_fY)); }

	Vec2 GetNormalized() const 
	{
		float fD = Abs(); if(fD <= 0.0f)
		{
			return Vec2(1.0f, 0.0f);
		}
		else { return Vec2(m_fX / fD, m_fY / fD); };
	};

	void Normalize() 
	{
		float fD = Abs(); if(fD <= 0.0f)
		{
			SetXY(1.0f, 0.0f, 0.0f);
		}
		else { m_fX /= fD; m_fY /= fD; };
	};

	Vec2 ElemMult(const Vec2& p_kxrA) const 
	{
		return Vec2(p_kxrA.m_fX*m_fX, p_kxrA.m_fY*m_fY);
	};

	float Distance(const Vec2& p_kvrV) const
	{
		return (*this - p_kvrV).Abs();
	}

	float DistanceSqr(const Vec2& p_kvrV) const
	{
		return (*this - p_kvrV).AbsSquare();
	}

	Vec2 Lerp(const Vec2 p_vTo, float p_fT) { return ((*this)*(1.0f - p_fT) + (p_vTo*p_fT)); };

	static Vec2 Zero;
	static Vec2 Up;
	static Vec2 Right;

	static void Register(lua_State* pL);
};

}	//	namespace neko