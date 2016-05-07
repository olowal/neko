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

bool AllocSpriteComponent(GameObject* pGameObject, luabridge::LuaRef data, const GFXDevice* pDevice)
{	
	if(pGameObject)
	{
		SpriteComponent* pC = Component<SpriteComponent>::Create(pGameObject);
		if(pC)
		{
			if(data["filename"] && data["filename"].isString())
			{
				const char* sFilename = data["filename"].cast<const char*>();
				
				pC->pTexture = pDevice->LoadTextureFromBinary(sFilename);

				int iX = 0;
				int iY = 0;
				int iW = 0;
				int iH = 0;

				if(data["x"] && data["x"].isNumber()) { iX=data["x"].cast<int>(); }
				if(data["y"] && data["y"].isNumber()) { iY=data["y"].cast<int>(); }
				if(data["w"] && data["w"].isNumber()) { iW=data["w"].cast<int>(); }
				if(data["h"] && data["h"].isNumber()) { iH=data["h"].cast<int>(); }

				return true;
			}
		}
	}

	return false;
}

}

template <>
void Component<SpriteComponent>::RegisterLua(lua_State* pL)
{
	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginNamespace("Components")
		.beginNamespace("Sprite")
		.addFunction("Alloc", AllocSpriteComponent)
		.endNamespace()
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
