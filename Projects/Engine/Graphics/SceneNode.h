/****************************************************************************
//	Filename: SceneNode.h
//	Description: A transform within a scene.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class SceneNode
{
public:
	SceneNode();
	virtual ~SceneNode();



protected:
	D2D1::Matrix3x2F m_mWorldTransform;
	D2D1::Matrix3x2F m_mLocalTransform;
};

}	//	namespace neko