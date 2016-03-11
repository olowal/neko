//	GameObject.cpp
#include "GameObject.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Engine/Framework/ScriptComponent.h"

#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"
using namespace luabridge;
namespace neko
{

const char* GameObject::ScriptHandle = "__gameObject";
const uint32 GameObject::NumGameObjects = 128;
ObjectPool<GameObject, false> GameObject::ms_pool(GameObject::NumGameObjects);
LinkedList<GameObject> GameObject::ms_getComponents;
LinkedList<GameObject> GameObject::ms_componentsToCheck;

GameObject::GameObject()
{
	m_pParent = NULL;
}

void GameObject::SetChanged()
{
	if(!m_bChanged)
	{
		ms_componentsToCheck.AddToLast(this);
		m_bChanged = true;
	}
}

void GameObject::Free(GameObject* pObj)
{
	printf("[GameObject::Free] Not yet implemented\n");
	ASSERT(false);
}


//	TODO: redo this at some point
void GameObject::UpdateComponents()
{
	for(auto it = ms_componentsToCheck.Begin(); !it.IsEnd(); ++it)
	{
		GameObject* pObj = (*it);
		ms_getComponents.AddToLast(pObj);
	}

	ms_componentsToCheck.Clear();

	for(auto it = ms_getComponents.Begin(); !it.IsEnd(); ++it)
	{
		GameObject* pObj = (*it);
		pObj->m_bChanged = false;
		ComponentManager::GetComponents(pObj);
	}

	ms_getComponents.Clear();
}

void GameObject::Init()
{
	const uint32 uSize = GameObject::NumGameObjects;
	for(uint32 i = 0; i < uSize; i++)
	{
		GameObject& obj = ms_pool.GetByIndex(i);
		obj.m_uIndex = i;
		obj.m_bChanged = false;
	}
}

void GameObject::Register(lua_State* pL)
{
	getGlobalNamespace(pL)
		.beginClass<GameObject>("GameObject")
		.endClass();
}

bool GameObject::Create(lua_State* pL, const char* szHandle)
{
	
	bool bOk = false;
	LuaRef obj = getGlobal(pL, szHandle);
	if(obj.isFunction())
	{
		obj = obj();
		GameObject* pObj = GameObject::Alloc();
		obj[GameObject::ScriptHandle] = pObj;
		LuaRef getComponents = obj["GetComponents"];
		LuaRef run = obj["Run"];
		LuaRef init = obj["Init"];

		if(getComponents.isFunction() && run.isFunction())
		{
			ScriptComponent* pC = Component<ScriptComponent>::Create(pObj);
			InitScriptComponent(pC, pL, obj);
			bOk = true;
		}

		if(init.isFunction())
		{
			init(obj);
			bOk = true;
		}

		if(!bOk)
		{
			GameObject::Free(pObj);
		}
	}

	return bOk;
}

}	// namespace neko
