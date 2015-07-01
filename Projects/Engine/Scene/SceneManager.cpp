//	SceneManager.cpp

#include "SceneManager.h"

namespace neko
{

SceneManager::SceneManager(){}
SceneManager::~SceneManager(){}

SceneManager::SceneNode::SceneNode():
	TransformNode(),
	m_pChild(NULL),
	m_pSibling(NULL){}
SceneManager::SceneNode::~SceneNode(){}

void SceneManager::SceneNode::AddChild(SceneNode* pChild)
{
	if(!m_pChild)
	{
		m_pChild = pChild;
	}
	else
	{
		m_pChild->AddChild(pChild);
	}
}

void SceneManager::SceneNode::Init()
{
	m_pChild = NULL;
	m_pSibling = NULL;
}

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
}

}	//	namespace neko