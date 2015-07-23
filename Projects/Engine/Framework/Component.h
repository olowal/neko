/****************************************************************************
//	Filename: Component.h
//	Description: Base for a component of some type
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class Component
{
public:
	Component(){}
	virtual ~Component(){}

	virtual void OnEnable(){}
	virtual void OnDisable(){}
};

}	//	namespace neko