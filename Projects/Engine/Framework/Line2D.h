/****************************************************************************
//	Filename: Line2D.h
//	Description: 2D representation of a circle
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Math/Vec2.h"
namespace neko
{
struct Line2D
{
	Vec2 start;
	Vec2 end;
};

static void SetStart(Line2D* pLine, float fX, float fY)
{
	pLine->start.SetXY(fX, fY);
}

static void SetEnd(Line2D* pLine, float fX, float fY)
{
	pLine->end.SetXY(fX, fY);
}

static void SetStartEnd(Line2D* pLine, float fXA, float fYA, float fXB, float fYB)
{
	pLine->start.SetXY(fXA, fYA);
	pLine->end.SetXY(fXB, fYB);
}

static Line2D* AllocLine2D(luabridge::LuaRef luaRef)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle].cast<GameObject*>();
	if(pObj)
	{
		Line2D* pLine = Component<Line2D>::Create(pObj);
		return pLine;
	}

	return NULL;
}

template <>
void Component<Line2D>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<Line2D>("Line2DComponent")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("CollisionShape")
		.beginNamespace("Line2D")
		.addFunction("SetStart", SetStart)
		.addFunction("SetEnd", SetEnd)
		.addFunction("SetStartEnd", SetStartEnd)
		.addFunction("Alloc", AllocLine2D)
		.endNamespace();
}

}	//	namespace neko
