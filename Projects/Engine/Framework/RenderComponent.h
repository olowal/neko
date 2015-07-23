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

class RenderComponent : public Component, public TransformNode
{
public:
	RenderComponent(){}
	virtual ~RenderComponent(){}

};

}	//	namespace neko