/****************************************************************************
//	Filename: Component.h
//	Description: Base for a component of some type
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class SceneNode;
class Component
{
public:
	Component(){}
	virtual ~Component(){}

	virtual void OnEnable(){}
	virtual void OnDisable(){}

	SceneNode* GetOwner() { return m_pOwner; }
	void SetOwner(SceneNode* pOwner) { m_pOwner = pOwner; }

protected:
	SceneNode* m_pOwner;
};

}	//	namespace neko