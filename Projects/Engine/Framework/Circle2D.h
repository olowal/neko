/****************************************************************************
//	Filename: Circle2D.h
//	Description: 2D representation of a circle
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Math/Vec2.h"
namespace neko
{
struct Circle2D
{
	Vec2 center;
	float radius;
};

static void SetCenter(Circle2D* pCircle, float fX, float fY)
{
	pCircle->center.SetXY(fX, fY);
}

static void SetRadius(Circle2D* pBox, float fRadius)
{
	pBox->radius = fRadius;
}

static Circle2D* AllocCircle2D(luabridge::LuaRef luaRef)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle].cast<GameObject*>();
	if(pObj)
	{
		Circle2D* pCircle = Component<Circle2D>::Create(pObj);
		return pCircle;
	}

	return NULL;
}

template <>
void Component<Circle2D>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<Circle2D>("Circle2DComponent")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("CollisionShape")
		.beginNamespace("Circle2D")
		.addFunction("SetCenter", (void(*)(Circle2D*, float, float))SetCenter)
		.addFunction("SetRadius", SetRadius)
		.addFunction("Alloc", AllocCircle2D)
		.endNamespace()
		.endNamespace();
}

}	//	namespace neko
