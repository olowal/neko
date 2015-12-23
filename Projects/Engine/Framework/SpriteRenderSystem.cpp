//	SpriteRenderSystem.cpp
#include "SpriteRenderSystem.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Engine/Graphics/GFXDevice.h"

namespace neko
{

bool SpriteRenderSystem::GetComponents(GameObject* pObj, Components* pComp)
{
	pComp->pTrans = Component<TransformComponent>::GetComponent(pObj);
	pComp->pSprite = Component<SpriteComponent>::GetComponent(pObj);

	return (pComp->pSprite != NULL && pComp->pTrans != NULL);
}

void SpriteRenderSystem::Run(Components* pComp, float fDelta)
{
	ASSERT(pComp->pSprite->pDevice != NULL);
	ASSERT(pComp->pSprite->pTexture != NULL);
	const Vec2& vPos = pComp->pTrans->vPos;
	pComp->pSprite->pDevice->DrawBitmap(vPos, pComp->pSprite->pTexture, pComp->pSprite->size, pComp->pTrans->fAngle);
}

}	//	namespace neko
