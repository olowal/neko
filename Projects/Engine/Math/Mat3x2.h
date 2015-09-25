/****************************************************************************
//	Filename: Mat3x2.h
//	Description: Extended version of D2D1::Matrix3x2F.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Vec2.h"

namespace neko
{

class Mat3x2 : public D2D1::Matrix3x2F
{
public:
	Mat3x2()
	{
		SetIdentity();
	}

	Mat3x2(const D2D1::Matrix3x2F& mM)
	{
		this->_11 = mM._11;
		this->_12 = mM._12;
		this->_21 = mM._21;
		this->_22 = mM._22;
		this->_31 = mM._31;
		this->_31 = mM._31;
	}
	virtual ~Mat3x2(){}

	Vec2 Pos() const
	{
		return Vec2(this->_31, this->_32);
	}

	void SetTranslation(const Vec2& vT)
	{
		this->_31 = vT.m_fX;
		this->_32 = vT.m_fY;
	}

	void SetTranslation(float fX, float fY)
	{
		this->_31 = fX;
		this->_32 = fY;
	}

	void Translate(const Vec2& vT)
	{
		this->_31 += vT.m_fX;
		this->_32 += vT.m_fY;
	}

	void Translate(float fX, float fY)
	{
		this->_31 += fX;
		this->_32 += fY;
	}
	void SetIdentity()
	{
		this->_11 = 1.0f;
		this->_12 = 0.0f;
		this->_21 = 0.0f;
		this->_22 = 1.0f;
		this->_31 = 0.0f;
		this->_32 = 0.0f;
	}
};

}	//	namespace neko