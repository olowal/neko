/****************************************************************************
//	Filename: TankControllerSystem.h
//	Description: Makes a tank move
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{
class GameObject;
struct TransformComponent;
}	//	namespace neko
struct TankControllerComponent;
struct TankPropertyComponent;
class TankControllerSystem
{
public:
	struct Components
	{
		TankControllerComponent* pCtrl;
		TankPropertyComponent* pProp;
		neko::TransformComponent* pTrans;
	};

	static bool GetComponents(neko::GameObject* pObj, Components* pComp);
	static void Run(Components* pComp, const float fDelta);
};