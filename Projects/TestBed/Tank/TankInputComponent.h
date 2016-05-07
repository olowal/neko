/****************************************************************************
//	Filename: TankInputComponent.h
//	Description: Settings for what buttons are used with controlling the tank.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
struct TankInputComponent
{
	uint32 forward;
	uint32 backward;
	uint32 left;
	uint32 right;
	uint32 fire;
};

namespace neko
{
void Component<TankInputComponent>::OnActivate(TankInputComponent* pC)
{
	pC->backward = 0;
	pC->forward = 0;
	pC->fire = 0;
	pC->left = 0;
	pC->right = 0;
}
}	//	namespace neko
