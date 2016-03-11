/****************************************************************************
//	Filename: GFXDeviceComponent.h
//	Description: A component that contains the gfx device used for rendering.
//	This component is only attached to the root parent of everything in the scene
//	this enabling everyone to get the GFXDevice for rendering if you want to 
//	draw stuff on the screen
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
namespace neko
{
class GFXDevice;
struct GFXDeviceComponent
{
	const GFXDevice* pDevice;
};

template <>
void Component<GFXDeviceComponent>::OnActivate(GFXDeviceComponent* pC)
{
	pC->pDevice = NULL;
}

}	//	namespace neko
