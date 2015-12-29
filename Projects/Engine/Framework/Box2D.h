/****************************************************************************
//	Filename: Box2D.h
//	Description: 2D representation of a box
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Math/Vec2.h"
namespace neko
{
struct Box2D
{
	Vec2 center;
	Vec2 extents;
};

static void SetCenter(Box2D* pBox, float fX, float fY)
{
	pBox->center.SetXY(fX, fY);
}

static void SetExtents(Box2D* pBox, float fX, float fY)
{
	pBox->extents.SetXY(fX, fY);
}

static Box2D* AllocBox2D(luabridge::LuaRef luaRef)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle].cast<GameObject*>();
	if(pObj)
	{
		Box2D* pBox = Component<Box2D>::Create(pObj);
		return pBox;
	}

	return NULL;
}

template <>
void Component<Box2D>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<Box2D>("Box2DComponent")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("CollisionShape")
		.beginNamespace("Box2D")
		.addFunction("SetCenter", (void(*)(Box2D*, float, float))SetCenter)
		.addFunction("SetExtents", SetExtents)
		.addFunction("Alloc", AllocBox2D)
		.endNamespace();
}

}	//	namespace neko
