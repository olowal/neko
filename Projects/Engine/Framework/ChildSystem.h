/****************************************************************************
//	Filename: ChildSystem.h
//	Description: Sets the transform component relative to the parent.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

class GameObject;
struct ChildComponent;
struct TransformComponent;
class ChildSystem
{
public:
	struct Components
	{
		TransformComponent* pTrans;
		ChildComponent* pChild;
	};

	static bool GetComponents(GameObject* pObj, Components* pComp);
	static void Run(Components* pComp, const float fDelta);
};

}	//	namespace neko
