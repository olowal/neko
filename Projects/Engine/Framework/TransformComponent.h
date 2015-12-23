/****************************************************************************
//	Filename: TransformComponent.h
//	Description: Position, rotation and scale in the world
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Math/Vec2.h"
#include "Engine/Math/Utils.h"

namespace neko
{

struct TransformComponent
{
	Vec2 vPos;
	Vec2 vScale;
	float fAngle;
};

namespace
{

void Translate(TransformComponent* pC, float fX, float fY)
{
	pC->vPos += Vec2(fX, fY);
}

void SetPosition(TransformComponent* pC, float fX, float fY)
{
	pC->vPos = Vec2(fX, fY);
}

void GetPosition(TransformComponent* pC, float& fX, float& fY)
{
	const Vec2& vPos = pC->vPos;
	fX = vPos.m_fX;
	fY = vPos.m_fY;
}

void Rotate(TransformComponent* pC, float fValue)
{
	pC->fAngle = neko::math::RotateAngle(pC->fAngle, fValue);
}

void SetAngle(TransformComponent* pC, float fValue)
{
	const float fAngle = neko::math::Clamp(fValue, 0.0f, math::DEGREE);
	pC->fAngle = fAngle;
}

float GetAngle(TransformComponent* pC)
{
	return pC->fAngle;
}

void Scale(TransformComponent* pC, float fX, float fY)
{
	pC->vScale += Vec2(fX, fY);
}

void SetScale(TransformComponent* pC, float fX, float fY)
{
	pC->vScale = Vec2(fX, fY);
}

void GetScale(TransformComponent* pC, float& fX, float& fY)
{
	const Vec2& vScale = pC->vScale;
	fX = vScale.m_fX;
	fY = vScale.m_fY;
}

TransformComponent* AllocTransformComponent(luabridge::LuaRef luaRef)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle].cast<GameObject*>();
	if(pObj)
	{
		TransformComponent* pC = Component<TransformComponent>::Create(pObj);
		return pC;
	}

	return NULL;
}

}

template <>
void Component<TransformComponent>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<TransformComponent>("TransformComponent")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("Transform")
		.addFunction("Translate", Translate)
		.addFunction("SetPosition", SetPosition)
		.addFunction("GetPosition", GetPosition)
		.addFunction("Rotate", Rotate)
		.addFunction("SetAngle", SetAngle)
		.addFunction("GetAngle", GetAngle)
		.addFunction("Scale", Scale)
		.addFunction("SetScale", SetScale)
		.addFunction("GetScale", GetScale)
		.addFunction("Alloc", AllocTransformComponent)
		.endNamespace();
}

template <>
void Component<TransformComponent>::OnActivate(TransformComponent* pC)
{
	pC->vPos = Vec2(0.0f, 0.0f);
	pC->vScale = Vec2(1.0f, 1.0f);
	pC->fAngle = 0.0f;
}

}	//	namespae neko
