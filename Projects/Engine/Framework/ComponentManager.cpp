//	ComponentManager.cpp
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "ScriptComponent.h"
#include "ChildComponent.h"
#include "Component.h"
#include "SpriteRenderSystem.h"
#include "ScriptSystem.h"
#include "ChildSystem.h"
#include "System.h"
#include "GameObject.h"

using namespace luabridge;

namespace neko
{

ComponentManager::ComponentManager(){}
ComponentManager::~ComponentManager(){}

void ComponentManager::Init(lua_State* pL)
{
	Component<TransformComponent>::Init();
	Component<ChildComponent>::Init();
	Component<SpriteComponent>::Init();
	Component<ScriptComponent>::Init();

	Component<TransformComponent>::RegisterLua(pL);
	Component<ChildComponent>::RegisterLua(pL);
	Component<SpriteComponent>::RegisterLua(pL);

	System<SpriteRenderSystem>::Init();
	System<ScriptSystem>::Init();
	System<ChildSystem>::Init();
}

void ComponentManager::Shut()
{
	System<SpriteRenderSystem>::Clear();
	System<ScriptSystem>::Clear();
	System<ChildSystem>::Clear();
}

void ComponentManager::Run(const float fDelta)
{
	System<ScriptSystem>::Run(fDelta);
	System<ChildSystem>::Run(fDelta);
	System<SpriteRenderSystem>::Run(fDelta);
}

void ComponentManager::GetComponents(GameObject* pObj)
{
	System<ChildSystem>::GetComponents(pObj);
	System<SpriteRenderSystem>::GetComponents(pObj);
	System<ScriptSystem>::GetComponents(pObj);
}

void ComponentManager::Free(GameObject* pObj)
{
	Component<TransformComponent>::Free(pObj);
	Component<ChildComponent>::Free(pObj);
	Component<SpriteComponent>::Free(pObj);
	Component<ScriptComponent>::Free(pObj);
}

}	//	namespace neko
