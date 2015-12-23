/****************************************************************************
//	Filename: SceneNode.h
//	Description: A node in a scene, can have a parent and/or children
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Scene/TransformNode.h"
#include "Engine/Core/LinkedList.h"

namespace neko
{

class SceneManager;
class Component;
class SceneNode : public TransformNode
{
public:
	SceneNode();
	virtual ~SceneNode();

	void AddChild(SceneNode* pChild);
	void RemoveChild(SceneNode* pChild);
	virtual SceneNode* CreateChildSceneNode();

	void Init(SceneManager* pRoot) { m_pRoot = pRoot; }	//	to be called from SceneManager only

protected:
	LinkedList<SceneNode> m_children;
	LinkedList<Component> m_components;
	SceneNode* m_pParent;
	SceneManager* m_pRoot;
};

}	//	namespace neko