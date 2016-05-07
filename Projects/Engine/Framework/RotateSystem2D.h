/****************************************************************************
//	Filename: RotateSystem2D.h
//	Description: Rotate a transform within specified angles
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{
struct TransformComponent;
struct RotatorComponent2D;
class GameObject;
class RotateSystem2D
{
	struct Components
	{
		TransformComponent* pTrans;
		RotatorComponent2D* pRotator;
	};

	static bool GetComponents(GameObject* pObj, Components* pComp);
	static void Run(Components* pComp, const float fDelta);
};
}	//	namespace neko
