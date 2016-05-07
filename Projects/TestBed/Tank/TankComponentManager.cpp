//	TankComponentManager.cpp
#include "TankComponentManager.h"

#include "Engine/Framework/SpriteComponent.h"
#include "Engine/Framework/TransformComponent.h"
#include "Engine/Framework/ScriptComponent.h"
#include "Engine/Framework/ChildComponent.h"
#include "Engine/Framework/Component.h"
#include "Engine/Framework/SpriteRenderSystem.h"
#include "Engine/Framework/ScriptSystem.h"
#include "Engine/Framework/ChildSystem.h"
#include "Engine/Framework/System.h"
#include "Engine/Framework/GameObject.h"

#include "TankControllerComponent.h"
#include "TankInputComponent.h"
#include "TankPropertyComponent.h"
#include "TankInputSystem.h"
#include "TankControllerSystem.h"

using namespace neko;

void TankComponentManager::Init(lua_State* pL)
{
	Inherited::Init(pL);
	Component<TankControllerComponent>::Init();
	Component<TankInputComponent>::Init();
	Component<TankPropertyComponent>::Init();
}

void TankComponentManager::Shut()
{
	Inherited::Shut();
	Component<TankControllerComponent>::Clear();
	Component<TankInputComponent>::Clear();
	Component<TankPropertyComponent>::Clear();
}

void TankComponentManager::Run(const float fDt)
{
	System<TankInputSystem>::Run(fDt);
	System<TankControllerSystem>::Run(fDt);
	System<ScriptSystem>::Run(fDt);
	System<ChildSystem>::Run(fDt);
	System<SpriteRenderSystem>::Run(fDt);
}
