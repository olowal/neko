/****************************************************************************
//	Filename: CollisionMasks.h
//	Description: A component containing data for collision masking
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
namespace neko
{
struct CollisionMasks
{
	uint32 masks;
	uint32 targets;
};

static void AddMask(CollisionMasks* pCollisionMasks, uint32 mask)
{
	pCollisionMasks->masks |= mask;
}

static void AddTarget(CollisionMasks* pCollisionMasks, uint32 target)
{
	pCollisionMasks->targets |= target;
}

static void RemoveMask(CollisionMasks* pCollisionMasks, uint32 mask)
{
	pCollisionMasks->masks &= ~(mask);
}

static void RemoveTarget(CollisionMasks* pCollisionMasks, uint32 target)
{
	pCollisionMasks->targets &= ~(target);
}

static CollisionMasks* AllocCollisionMasks(luabridge::LuaRef luaRef)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle].cast<GameObject*>();
	if(pObj)
	{
		CollisionMasks* pCollisionMasks = Component<CollisionMasks>::Create(pObj);
		return pCollisionMasks;
	}

	return NULL;
}

template <>
void Component<CollisionMasks>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<CollisionMasks>("CollisionMasks")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("CollisionMask")
		.addFunction("AddTarget", AddTarget)
		.addFunction("AddMask", AddMask)
		.addFunction("RemoveMask", RemoveMask)
		.addFunction("RemoveTarget", RemoveTarget)
		.endNamespace();
}

template <>
void Component<CollisionMasks>::OnActivate(CollisionMasks* pC)
{
	pC->masks = 0;
	pC->targets = 0;
}

}	//	namespace neko
