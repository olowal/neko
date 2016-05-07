/****************************************************************************
//	Filename: RotatorComponent2D.h
//	Description: Define the limits of the rotation for a 2D transform.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
namespace neko
{
struct RotatorComponent2D
{
	float min;
	float max;
	float target;
	float speed;
};

template <>
void Component<RotatorComponent2D>::OnActivate(RotatorComponent2D* pC)
{
	pC->min = 0.0f;
	pC->max = 0.0f;
}

}	//	namespace neko
