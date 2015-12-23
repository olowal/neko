//	ScriptSystem.cpp
#include "ScriptSystem.h"
#include "Component.h"
#include "ScriptComponent.h"

using namespace luabridge;

namespace neko
{

bool ScriptSystem::GetComponents(GameObject* pObj, Components* pComp)
{
	pComp->pScript = Component<ScriptComponent>::GetComponent(pObj);
	if(pComp->pScript != NULL)
	{
		LuaRef& luaRef = (*pComp->pScript->pLuaRef);
		LuaRef init = luaRef["GetComponents"];
		LuaRef run = luaRef["Run"];

		if(init.isFunction() && run.isFunction())
		{
			bool bOk = init((*pComp->pScript->pLuaRef));
			return bOk;
		}
	}
	
	return false;
}

void ScriptSystem::Run(Components* pComp, const float fDelta)
{
	ASSERT(pComp->pScript->pL != NULL);
	ASSERT(pComp->pScript->pLuaRef != NULL);

	LuaRef& obj = *pComp->pScript->pLuaRef;
	LuaRef run = obj["Run"];
	run(obj);
}

}	//	namespace neko
