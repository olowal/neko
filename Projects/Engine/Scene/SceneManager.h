/****************************************************************************
//	Filename: SceneManager.h
//	Description: Manages a scene of nodes.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/LinkedList.h"
#include "Engine/Scene/TransformNode.h"

namespace neko
{

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	TransformNode* CreateSceneNode(const TransformNode* pParent);
	void DeleteSceneNode(const TransformNode* pNode);

protected:
	class SceneNode : public TransformNode
	{
	public:
		SceneNode();
		~SceneNode();

		enum { SCENE_NODE_ID = 0x56549549 };
		virtual uint32 GetId() const { return SCENE_NODE_ID; }

		void Init();
		void PreCullUpdate(SceneNode* pParent = NULL, bool bParentDirty = false);
		void AddChild(SceneNode* pChild);

	private:
		void AddSibling(SceneNode* pSibling);

		SceneNode* m_pChild;
		SceneNode* m_pSibling;
	};

	ObjectPool<SceneNode> m_sceneNodes;
	LinkedList<SceneNode> m_parentSceneNodes;
};

}	//	namespace neko