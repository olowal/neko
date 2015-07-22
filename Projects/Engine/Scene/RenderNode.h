/****************************************************************************
//	Filename: RenderNode.h
//	Description: Renders things in the world.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class SceneManager;
class TransformNode;
class RenderGroup;
class RenderNode
{
public:
	RenderNode();
	virtual ~RenderNode();

	enum Layer
	{
		Layer_Background = 0,
		Layer_World,
		Layer_Overlay,
		Layer_Count
	};

	enum ComparisonMask
	{
		//Comparison_Mask_Priority
	};

	enum ComparisonShift
	{
	
	};

	void SetParent(RenderGroup* pParent);
	void SetLayer(Layer eLayer) { ASSERT(eLayer < Layer_Count); m_eLayer = eLayer; }
	void SetPriority(uint8 uPriority) { m_uPriority = uPriority; SetPriorityCmpValue(); }

	Layer GetLayer() const { return m_eLayer; }
	uint8 GetPriority() const { return m_uPriority; }

	bool operator<(const RenderNode& node) const;
	bool operator>(const RenderNode& node) const;

	virtual bool Draw() { ASSERT(false); return false; }

protected:
	void SetPriorityCmpValue();

private:
	PRIVATE_COPY(RenderNode);
	RenderGroup* m_pParent;
	uint32 m_uComparisonVal;
	Layer m_eLayer;
	uint8 m_uPriority;
};

}	//	namespace neko