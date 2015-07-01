//	TransformNode.cpp

#include "TransformNode.h"

namespace neko
{

TransformNode::TransformNode()
{
	m_mWorldTransform.SetIdentity();
	m_mLocalTransform.SetIdentity();
	m_bLocalMatDirty = false;
}

TransformNode::~TransformNode()
{

}

void TransformNode::SetMatrix(const Mat3x2& mat)
{
	m_mLocalTransform = mat;
	m_bLocalMatDirty = true;
}

}	//	namespace neko