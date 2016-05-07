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

bool AllocTransformComponent(GameObject* pGameObject, luabridge::LuaRef data)
{
	if(pGameObject)
	{
		TransformComponent* pC = Component<TransformComponent>::Create(pGameObject);
		if(pC)
		{
			if(data["x"] && data["x"].isNumber()) {		pC->vPos.m_fX	=	data["x"].cast<float>(); }
			if(data["y"] && data["y"].isNumber()) {		pC->vPos.m_fY	=	data["y"].cast<float>(); }
			if(data["w"] && data["w"].isNumber()) {		pC->vScale.m_fX	=	data["w"].cast<float>(); }
			if(data["h"] && data["h"].isNumber()) {		pC->vScale.m_fY	=	data["h"].cast<float>(); }
			if(data["angle"] && data["angle"].isNumber()) { pC->fAngle	=	data["angle"].cast<float>(); }

			return true;
		}
	}

	return false;
}

}

template <>
void Component<TransformComponent>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;

	getGlobalNamespace(pL)
		.beginNamespace("Component")
		.beginNamespace("Transform")
		.addFunction("Alloc", AllocTransformComponent)
		.endNamespace()
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
