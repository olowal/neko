/****************************************************************************
//	Filename: TankPropertyComponent.h
//	Description: Contains data for handling a tank
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/Component.h"
struct TankPropertyComponent
{
	float movementSpeed;
	float rotationSpeed;
};

static bool AllocTankPropertyComponent(neko::GameObject* pGameObject, luabridge::LuaRef data)
{
	if(pGameObject)
	{
		TankPropertyComponent* pC = Component<TankPropertyComponent>::Create(pGameObject);
		if(pC)
		{
			if(data["movementSpeed"] && data["movementSpeed"].isNumber()) { pC->movementSpeed = data["movementSpeed"].cast<float>(); }
			if(data["rotationSpeed"] && data["rotationSpeed"].isNumber()) { pC->rotationSpeed = data["rotationSpeed"].cast<float>(); }
			return true;
		}
	}

	return false;
}

namespace neko
{
template <>
void Component<TankPropertyComponent>::OnActivate(TankPropertyComponent* pC)
{
	pC->movementSpeed = 0.0f;
	pC->rotationSpeed = 0.0f;
}
}	//	namespace neko
