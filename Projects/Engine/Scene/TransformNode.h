/****************************************************************************
//	Filename: TransformNode.h
//	Description: A transform within a scene.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Mat3x2.h"

namespace neko
{

class TransformNode
{
public:
	TransformNode();
	virtual ~TransformNode();

	virtual uint32 GetId() const = 0;

	void SetMatrix(const Mat3x2& mat);

	const Mat3x2& GetMatrix() const { return m_mWorldTransform; }
	const Mat3x2& GetLocalMatrix() const { return m_mLocalTransform; }

protected:
	Mat3x2 m_mWorldTransform;
	Mat3x2 m_mLocalTransform;

	bool m_bLocalMatDirty;
};

}	//	namespace neko