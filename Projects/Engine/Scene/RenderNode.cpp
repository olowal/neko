//	RenderNode.cpp

#include "RenderNode.h"

namespace neko
{

RenderNode::RenderNode(){}
RenderNode::~RenderNode(){}

void RenderNode::SetParent(RenderGroup* pParent)
{
	m_pParent = pParent;
}

void RenderNode::SetPriorityCmpValue()
{

}

}	//	namespace neko