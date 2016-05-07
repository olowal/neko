//	RotateSystem.cpp
#include "RotateSystem2D.h"
#include "Engine/Framework/TransformComponent.h"
#include "Engine/Framework/RotatorComponent2D.h"

namespace neko
{
static float s_fMinDiff = 0.5f;
static float s_fLean = 1.4f;
bool RotateSystem2D::GetComponents(GameObject* pObj, Components* pComp)
{
	if(Component<TransformComponent>::GetComponent(&pComp->pTrans, pObj)
		&& Component<RotatorComponent2D>::GetComponent(&pComp->pRotator, pObj))
	{
		return true;
	}

	return false;
}

void RotateSystem2D::Run(Components* pComp, const float fDelta)
{
	TransformComponent& trans = *pComp->pTrans;
	RotatorComponent2D& rot = *pComp->pRotator;

	float fTargetAngle = rot.target;

	float fDiff = fabsf((fabsf(trans.fAngle) - rot.target));
	if(fDiff > s_fMinDiff)
	{
		//float dir = Mathf.Sign(((((target - current) % 360) + 540) % 360) - 180);    //  Get the shortest angle
		float fDir = (float)math::Sign((((static_cast<int>(rot.target - trans.fAngle) % 360) + 540) % 360) - 180);	// get the shortest direction to target
		float fSpeed = rot.speed * fDelta;
		float fAngle = math::RotateAngle(trans.fAngle, (fDir * fSpeed) * (fDiff < s_fLean ? (fDiff / s_fLean) : 1.0f));
		fAngle = math::Clamp(fAngle, rot.min, rot.max);
		trans.fAngle = fAngle;
	}
	else
	{
		float fAngle = math::Clamp(rot.target, rot.min, rot.max);
		trans.fAngle = fAngle;
	}
}
}	//	namespace neko
