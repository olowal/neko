//	SceneNode.cpp
#include "SceneNode.h"
#include "SceneManager.h"

namespace neko
{

SceneNode::SceneNode():
m_pParent(NULL),
m_pRoot(NULL)

{
	int p = 0;
	p++;
}

SceneNode::~SceneNode()
{
	if(m_pParent != NULL)
	{
		m_pParent->RemoveChild(this);
	}
}

void SceneNode::AddChild(SceneNode* pChild)
{
	m_children.AddToLast(pChild);
}

void SceneNode::RemoveChild(SceneNode* pChild)
{
	m_children.Remove(pChild);
}

SceneNode* SceneNode::CreateChildSceneNode()
{
	ASSERT(m_pRoot != NULL);
	return m_pRoot->CreateSceneNode(this);
}

}	//	namespace neko