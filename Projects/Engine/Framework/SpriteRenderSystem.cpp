//	SpriteRenderSystem.cpp
#include "SpriteRenderSystem.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "GFXDeviceComponent.h"
#include "Engine/Graphics/GFXDevice.h"

namespace neko
{

bool SpriteRenderSystem::GetComponents(GameObject* pObj, Components* pComp)
{
	return Component<TransformComponent>::GetComponent(&pComp->pTrans, pObj)
		&& Component<SpriteComponent>::GetComponent(&pComp->pSprite, pObj)
		&& Component<GFXDeviceComponent>::GetComponentFromParentRecursive(&pComp->pGFX, pObj);
}

void SpriteRenderSystem::Run(Components* pComp, const float fDelta)
{
	//ASSERT(pComp->pSprite->pDevice != NULL);
	ASSERT(pComp->pSprite->pTexture != NULL);
	const GFXDevice* pDevice = pComp->pGFX->pDevice;
	const Vec2& vPos = pComp->pTrans->vPos;
	pDevice->DrawBitmap(vPos, pComp->pSprite->pTexture, pComp->pSprite->size, pComp->pTrans->fAngle);
}

}	//	namespace neko
