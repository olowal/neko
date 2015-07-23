/****************************************************************************
//	Filename: SceneManager.h
//	Description: Manages a scene of nodes.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/LinkedList.h"
#include "Engine/Scene/SceneNode.h"

namespace neko
{

class SceneManager : public SceneNode
{
public:
	SceneManager();
	virtual ~SceneManager();

	SceneNode* CreateSceneNode(SceneNode* pParent);
	void DeleteSceneNode(SceneNode* pNode);
	virtual SceneNode* CreateChildSceneNode();

protected:

	ObjectPool<SceneNode> m_nodePool;
};

}	//	namespace neko