//	TankControllerSystem.cpp
#include "TankControllerSystem.h"
#include "Engine/Framework/TransformComponent.h"
#include "TankControllerComponent.h"
#include "TankPropertyComponent.h"
using namespace neko;

bool TankControllerSystem::GetComponents(GameObject * pObj, Components * pComp)
{
	if(Component<TransformComponent>::GetComponent(&pComp->pTrans, pObj)
		&& Component<TankPropertyComponent>::GetComponent(&pComp->pProp, pObj)
		&& Component<TankControllerComponent>::GetComponent(&pComp->pCtrl, pObj))
	{
		return true;
	}
	return false;
}

void TankControllerSystem::Run(Components * pComp, const float fDelta)
{
	TankPropertyComponent& prop = *pComp->pProp;
	TankControllerComponent& ctrl = *pComp->pCtrl;
	TransformComponent& trans = *pComp->pTrans;

	trans.fAngle = math::RotateAngle(trans.fAngle, (prop.rotationSpeed * fDelta) * ctrl.turn);
	const Vec2 dir = math::AngleToDirection(trans.fAngle);
	trans.vPos += dir * (prop.movementSpeed * fDelta) * ctrl.throttle;
}
