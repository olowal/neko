/****************************************************************************
//	Filename: Camera.h
//	Description: It is a camera, a mtrix multiplier
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Mat3x2.h"

namespace neko
{

class Camera
{
public:
	Camera()
	{
		m_mModel.SetIdentity();
	}
	~Camera(){}

	const Vec2 GetPosition() const { return m_mModel.Pos(); }
	const Mat3x2& GetModelMatrix() const { return m_mModel; }
	const Mat3x2& GetViewMatrix() const { return m_mView; }

	void Translate(const Vec2& vTranslation)
	{
		m_mModel.SetTranslation(m_mModel.Pos() + vTranslation);
	}

	void SetPosition(const Vec2& vPos)
	{
		m_mModel.SetTranslation(vPos);
	}

private:
	Mat3x2 m_mModel;
	Mat3x2 m_mView;
};

}	//	namespace neko