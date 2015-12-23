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
	
	~Mat3x2(){}

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

	void Scale(float fWidth, float fHeight, const Vec2& vCenter)
	{
		this->_11 = fWidth;
		this->_12 = 0.0f;
		this->_21 = 0.0f;
		this->_22 = fHeight;
		this->_31 = vCenter.m_fX - fWidth * vCenter.m_fX;
		this->_32 = vCenter.m_fY - fHeight * vCenter.m_fY;
	}

	void Scale(float fWidth, float fHeight, float fX, float fY)
	{
		Scale(fWidth, fHeight, Vec2(fX, fY));
	}

	void Scale(const Vec2& vScale, const Vec2& vCenter)
	{
		Scale(vScale.m_fX, vScale.m_fY, vCenter.m_fX, vCenter.m_fY);
	}

	void Rotate(float fAngle, const Vec2& vCenter)
	{
		// not yet implemented
		ASSERT(false);
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

private:
	float _11;
	float _12;
	float _21;
	float _22;
	float _31;
	float _32;
};

}	//	namespace neko