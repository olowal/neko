//	SceneManager.cpp

#include "SceneManager.h"

namespace neko
{

SceneManager::SceneManager() : 
	m_nodePool(128){}
SceneManager::~SceneManager(){}

/*
void SceneManager::SceneNode::PreCullUpdate(SceneNode* pParent, bool bParentDirty)
{
	if(bParentDirty || m_bLocalMatDirty)
	{
		if(pParent)
		{
			m_mWorldTransform = m_mLocalTransform * pParent->GetMatrix();
		}
		else
		{
			m_mWorldTransform = m_mLocalTransform;
		}
	}

	if(m_pSibling)
	{
		m_pSibling->PreCullUpdate(pParent, bParentDirty);
	}

	if(m_pChild)
	{
		m_pChild->PreCullUpdate(this, bParentDirty|m_bLocalMatDirty);
	}
}

void SceneManager::SceneNode::AddSibling(SceneNode* pSibling)
{
	if(!m_pSibling)
	{
		m_pSibling = pSibling;
	}
	else
	{
		m_pSibling->AddSibling(pSibling);
	}
}*/

SceneNode* SceneManager::CreateSceneNode(SceneNode* pParent)
{
	SceneNode* pSceneNode = m_nodePool.Alloc();
	pSceneNode->Init(this);

	if(pParent)
	{
		pParent->AddChild(pSceneNode);
	}

	return pSceneNode;
}

SceneNode* SceneManager::CreateChildSceneNode()
{
	return CreateSceneNode(this);
}

void SceneManager::DeleteSceneNode(SceneNode* pNode)
{
	m_nodePool.Free(pNode);
}

}	//	namespace neko