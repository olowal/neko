/****************************************************************************
//	Filename: RenderComponent.h
//	Description: Can draw things on the screen
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Scene/TransformNode.h"

namespace neko
{

class Texture;
class GFXDevice;
class RenderComponent : public Component, public TransformNode
{
public:
	RenderComponent(){}
	virtual ~RenderComponent(){}

	enum Layer
	{
		Layer_Background = 0,
		Layer_World,
		Layer_Overlay,
		Layer_Count
	};

	void Draw(GFXDevice* pDevice);
	void SetLayer(Layer eLayer) { m_eLayer = eLayer; }
	Layer GetLayer() const { return m_eLayer; }

private:
	Texture* m_pTexture;
	Layer m_eLayer;
};

}	//	namespace neko