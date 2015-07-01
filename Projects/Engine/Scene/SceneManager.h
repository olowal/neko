/****************************************************************************
//	Filename: SceneManager.h
//	Description: Manages a scene of nodes.
*****************************************************************************/

#pragma once

#include "Engine/Common/Common.h"
#include "Engine/Scene/TransformNode.h"

namespace neko
{

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

protected:
	class SceneNode : public TransformNode
	{
	public:
		SceneNode();
		~SceneNode();

		enum { SCENE_NODE_ID = 0x56549549 };
		virtual uint32 GetId() const { return SCENE_NODE_ID; }

		void AddChild(SceneNode* pChild);

	private:
		void AddSibling(SceneNode* pSibling);

		SceneNode* m_pChild;
		SceneNode* m_pSibling;
	};
};

}	//	namespace neko