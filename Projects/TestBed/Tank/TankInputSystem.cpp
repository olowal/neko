//	TankInputSystem.cpp
#include "TankInputSystem.h"
#include "TankInputComponent.h"
#include "TankControllerComponent.h"
#include "Engine/Framework/Input.h"
using namespace neko;
bool TankInputSystem::GetComponents(neko::GameObject * pObj, Components * pComp)
{
	if(Component<TankInputComponent>::GetComponent(&pComp->input, pObj)
		&& Component<TankControllerComponent>::GetComponent(&pComp->ctrl, pObj))
	{
		return true;
	}
	return false;
}

void TankInputSystem::Run(Components * pComp, const float fDelta)
{
	TankInputComponent& input = *pComp->input;
	TankControllerComponent& ctrl = *pComp->ctrl;
	if(Input::IsKeyDown(input.forward))
	{
		ctrl.throttle = 1.0f;
	}
	else if(Input::IsKeyDown(input.backward))
	{
		ctrl.throttle = -1.0f;
	}
	if(Input::IsKeyDown(input.right))
	{
		ctrl.turn = 1.0f;
	} 
	else if(Input::IsKeyDown(input.left))
	{
		ctrl.turn = -1.0f;
	}

	ctrl.fire = Input::IsKeyPressed(input.fire);
}
