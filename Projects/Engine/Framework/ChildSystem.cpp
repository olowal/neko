//	ChildSystem.cpp
#include "ChildSystem.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ChildComponent.h"

namespace neko
{

bool ChildSystem::GetComponents(GameObject* pObj, Components* pComp)
{
	pComp->pTrans = Component<TransformComponent>::GetComponent(pObj);
	pComp->pChild = Component<ChildComponent>::GetComponent(pObj);

	return (pComp->pChild != NULL && pComp->pTrans != NULL);
}

void ChildSystem::Run(Components* pComp, float fDelta)
{
	const float fParentAngle = pComp->pChild->pParentTrans->fAngle;
	const Vec2& vParentPos = pComp->pChild->pParentTrans->vPos;

	const float fAngle = pComp->pTrans->fAngle;
	const Vec2& vPos = pComp->pTrans->vPos;

	const float fC = cosf(math::Deg2Rad(fParentAngle));
	const float fS = sinf(math::Deg2Rad(fParentAngle));

	const float fX = (vPos.m_fX * fC) - (vPos.m_fY * fS);
	const float fY = (vPos.m_fX * fS) + (vPos.m_fY * fC);

	pComp->pTrans->vPos = vParentPos + Vec2(fX, fY);
	pComp->pTrans->fAngle = fParentAngle + fAngle;
}

}	//	namespace neko
