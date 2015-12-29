//	ComponentManager.cpp
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "ScriptComponent.h"
#include "ChildComponent.h"
#include "CollisionMasks.h"
#include "Box2D.h"
#include "Circle2D.h"
#include "Line2D.h"
#include "Component.h"
#include "SpriteRenderSystem.h"
#include "ScriptSystem.h"
#include "ChildSystem.h"
#include "System.h"
#include "GameObject.h"

using namespace luabridge;

namespace neko
{

static lua_State* s_pL = NULL;

ComponentManager::ComponentManager(){}
ComponentManager::~ComponentManager()
{
	s_pL = NULL;
}

void ComponentManager::Init(lua_State* pL)
{
	Component<TransformComponent>::Init();
	Component<ChildComponent>::Init();
	Component<SpriteComponent>::Init();
	Component<ScriptComponent>::Init();
	Component<CollisionMasks>::Init();
	Component<Box2D>::Init();
	Component<Circle2D>::Init();
	Component<Line2D>::Init();

	Component<TransformComponent>::RegisterLua(pL);
	Component<ChildComponent>::RegisterLua(pL);
	Component<SpriteComponent>::RegisterLua(pL);
	Component<CollisionMasks>::RegisterLua(pL);
	Component<Box2D>::RegisterLua(pL);
	Component<Circle2D>::RegisterLua(pL);
	Component<Line2D>::RegisterLua(pL);

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
	Component<CollisionMasks>::Free(pObj);
	Component<Box2D>::Free(pObj);
	Component<Circle2D>::Free(pObj);
	Component<Line2D>::Free(pObj);
}

}	//	namespace neko
