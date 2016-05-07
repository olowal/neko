/****************************************************************************
//	Filename: TankControllerComponent.h
//	Description: Data for translating a tank
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
struct TankControllerComponent
{
	float throttle;
	float turn;
	bool fire;
};

namespace neko
{
template <>
void Component<TankControllerComponent>::OnActivate(TankControllerComponent* pC)
{
	pC->throttle = 0.0f;
	pC->turn = 0.0f;
	pC->fire = false;
}
}	//	namespace neko
