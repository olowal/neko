/****************************************************************************
//	Filename: SpriteComponent.h
//	Description: Can draw things on the screen
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
#include "Engine/Graphics/GFXDevice.h"

namespace neko
{

struct SpriteComponent
{
	SDL_Texture* pTexture;
	const GFXDevice* pDevice;
	SDL_Rect size;
};

namespace
{

void SetDimension(SpriteComponent* pC, int iX, int iY, int iW, int iH)
{
	pC->size.x = iX;
	pC->size.y = iY;
	pC->size.w = iW;
	pC->size.h = iH;
}

void LoadTexture(SpriteComponent* pC, const char* szFilename)
{
	ASSERT(pC->pDevice != NULL);
	pC->pTexture = pC->pDevice->LoadTextureFromBinary(szFilename);
}

SpriteComponent* AllocSpriteComponent(luabridge::LuaRef luaRef)
{
	GameObject* pObj = luaRef[GameObject::ScriptHandle].cast<GameObject*>();
	
	if(pObj)
	{
		SpriteComponent* pC = Component<SpriteComponent>::Create(pObj);
		return pC;
	}

	return NULL;
}

}

template <>
void Component<SpriteComponent>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<SpriteComponent>("SpriteComponent")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("Sprite")
		.addFunction("LoadTexture", LoadTexture)
		.addFunction("SetDimension", SetDimension)
		.addFunction("Alloc", AllocSpriteComponent)
		.endNamespace();
}

template <>
void Component<SpriteComponent>::OnActivate(SpriteComponent* pC)
{
	pC->pTexture = NULL;
	pC->pDevice = GFXDevice::GetDevice();
	pC->size.x = 0;
	pC->size.y = 0;
	pC->size.w = 0;
	pC->size.h = 0;
}

}	//	namespace neko
