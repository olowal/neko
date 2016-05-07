//	ChildSystem.cpp
#include "ChildSystem.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ChildComponent.h"

namespace neko
{

bool ChildSystem::GetComponents(GameObject* pObj, Components* pComp)
{
	if(Component<TransformComponent>::GetComponent(&pComp->pTrans, pObj)
		&& Component<TransformComponent>::GetComponentFromParent(&pComp->pParentTransform, pObj))
	{
		return true;
	}
	return false;
}

void ChildSystem::Run(Components* pComp, const float fDelta)
{
	const float fParentAngle = pComp->pParentTransform->fAngle;
	const Vec2& vParentPos = pComp->pParentTransform->vPos;

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
