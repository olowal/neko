/****************************************************************************
//	Filename: ChildComponent.h
//	Description: A child to a parent
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Framework/TransformComponent.h"
namespace neko
{

struct ChildComponent
{
	TransformComponent* pParentTrans;
};

namespace
{

void InitChildComponent(ChildComponent* pC, GameObject* pObj)
{
	TransformComponent* pParentTrans = Component<TransformComponent>::GetComponent(pObj);
}

void AllocChildComponent(luabridge::LuaRef luaRef, luabridge::LuaRef parent)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle];
	GameObject* pParentObj = parent[GameObject::ScriptHandle];
	if(pObj && pParentObj)
	{
		ChildComponent* pC = Component<ChildComponent>::Create(pObj);
		InitChildComponent(pC, pParentObj);
	}
}

}

template <>
void Component<ChildComponent>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<ChildComponent>("ChildComponent")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("Child")
		.addFunction("Alloc", AllocChildComponent)
		.endNamespace();
}

template <>
void Component<ChildComponent>::OnActivate(ChildComponent* pC)
{
	pC->pParentTrans = NULL;
}

}	//	namespace neko
