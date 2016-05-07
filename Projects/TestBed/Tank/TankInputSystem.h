/****************************************************************************
//	Filename: TankInputSystem.h
//	Description: Translates input settings to the controller
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{
class GameObject;
}	//	namespace neko
struct TankInputComponent;
struct TankControllerComponent;
class TankInputSystem
{
public:
	struct Components
	{
		TankInputComponent* input;
		TankControllerComponent* ctrl;
	};

	static bool GetComponents(neko::GameObject* pObj, Components* pComp);
	static void Run(Components* pComp, const float fDelta);
};