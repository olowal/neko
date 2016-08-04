//	GameObject.cpp
#include "GameObject.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Engine/Framework/ScriptComponent.h"
#include "Engine/Framework/GameObjectID.h"

#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"
using namespace luabridge;
namespace neko
{

const char* GameObject::ScriptHandle = "__gameObject";
const uint32 GameObject::NumGameObjects = 128;
ObjectPool<GameObject> GameObject::ms_pool(GameObject::NumGameObjects);
LinkedList<GameObject> GameObject::ms_getComponents;
LinkedList<GameObject> GameObject::ms_componentsToCheck;
GameObject* GameObject::ms_pRoot = NULL;

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

		for(LinkedList<GameObject>::Iterator it = m_children.Begin(); !it.IsEnd(); ++it)
		{
			(*it)->SetChanged();
		}
	}
}

GameObject* GameObject::Alloc(bool bAddToRoot)
{
	GameObject* pObj = ms_pool.Alloc();
	if(pObj)
	{
		GameObjectID* gameObjectID = Component<GameObjectID>::Create(pObj);
		gameObjectID->gameObject = pObj;
		if(bAddToRoot)
		{
			pObj->m_pParent = ms_pRoot;
			ms_pRoot->m_children.AddToLast(pObj);
		}
	}
	return NULL;
}

uint32 GameObject::lua_AllocGameObject()
{
	GameObject* pGameObject = GameObject::Alloc();
	
	if(pGameObject)
	{
		return pGameObject->GetIndex();
	}

	return 0;
}

uint32 GameObject::lua_AllocChildGameObject(uint32 uParentIdx)
{
	GameObject* pParent = &ms_pool.GetByIndex(uParentIdx);
	if(pParent)
	{
		GameObject* pGameObject = GameObject::Alloc(pParent);
		if(pGameObject)
		{
			return pGameObject->GetIndex();
		}
	}
	
	return 0;
}

GameObject* GameObject::Alloc(GameObject* pParent)
{
	GameObject* pObj = GameObject::Alloc(false);
	if(pObj)
	{
		pObj->m_pParent = pParent;
		pParent->m_children.AddToLast(pObj);
	}
	return NULL;
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

GameObject* GameObject::Init()
{
	const uint32 uSize = GameObject::NumGameObjects;
	for(uint32 i = 0; i < uSize; i++)
	{
		GameObject& obj = ms_pool.GetByIndex(i);
		obj.m_uIndex = i;
		obj.m_bChanged = false;
	}

	ms_pRoot = ms_pool.Alloc();
	ASSERT(ms_pRoot != NULL);
	return ms_pRoot;
}

void GameObject::Register(lua_State* pL)
{
	getGlobalNamespace(pL)
		.beginNamespace("_GameObject")
		.addFunction("Create", &GameObject::lua_AllocGameObject)
		.addFunction("CreateChild", &GameObject::lua_AllocChildGameObject)
		.endNamespace();
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
