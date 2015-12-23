/****************************************************************************
//	Filename: ScriptSystem.h
//	Description: Runs a script for a game object
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

class GameObject;
struct ScriptComponent;
class ScriptSystem
{
public:
	struct Components
	{
		ScriptComponent* pScript;
	};

	static bool GetComponents(GameObject* pObj, Components* pComp);
	static void Run(Components* pComp, float fDelta);
};

}	//	namespace neko
