/****************************************************************************
//	Filename: ScriptComponent.h
//	Description: Runs a lua script
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
namespace neko
{

struct ScriptComponent
{
	luabridge::LuaRef* pLuaRef;
	lua_State* pL;
};

namespace
{

bool InitScriptComponent(ScriptComponent* pC, lua_State* pL, luabridge::LuaRef obj)
{
	if(pC->pLuaRef == NULL && pL != NULL)
	{
		using namespace luabridge;
		
		pC->pLuaRef = new luabridge::LuaRef(pL);
		(*pC->pLuaRef) = obj;
		pC->pL = pL;
		return true;
	}

	return false;
}

}

template <>
void Component<ScriptComponent>::OnActivate(ScriptComponent* pC)
{
	pC->pLuaRef = NULL;
	pC->pL = NULL;
}

template <>
void Component<ScriptComponent>::OnDeactivate(ScriptComponent* pC)
{
	if(pC->pLuaRef != NULL)
	{
		delete pC->pLuaRef;
		pC->pLuaRef = NULL;
	}
}

}	//	namespace neko
