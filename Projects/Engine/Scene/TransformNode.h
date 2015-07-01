/****************************************************************************
//	Filename: TransformNode.h
//	Description: A transform within a scene.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Mat3x2.h"
#include "Engine/Physics2D/CollisionSphere2D.h"

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
	void UpdateWorldSphere();

	Mat3x2 m_mWorldTransform;
	Mat3x2 m_mLocalTransform;

	CollisionSphere2D m_relSphere;
	CollisionSphere2D m_worldSphere;

	bool m_bLocalMatDirty;
};

inline void TransformNode::UpdateWorldSphere()
{
	Vec2 vPos = m_relSphere.GetPosition() * m_mWorldTransform;
	m_worldSphere.SetPosition(vPos);
}

}	//	namespace neko