/****************************************************************************
//	Filename: Component.h
//	Description: Get, create and fee components with this manager
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/GameObject.h"
#include "Engine/Core/ObjectPool.h"
#include "Engine/Core/LinkedList.h"
#include "Engine/Core/DArray.h"
#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"

namespace neko
{

template <class ComponentType>
class Component
{
public:
	static ComponentType* GetComponent(const GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		ComponentType* pC = ms_allocations[uIndex] ? &ms_components[uIndex] : NULL;
		return pC;
	}

	static ComponentType* GetComponent(ComponentType** ppC, const GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		ComponentType* pC = (*ppC) = ms_allocations[uIndex] ? &ms_components[uIndex] : NULL;
		return pC;
	}

	static ComponentType* GetComponentFromParent(ComponentType** ppC, const GameObject* pObj)
	{
		const GameObject* pParent = pObj->GetParent();
		ComponentType* pC = NULL;
		if(pParent)
		{
			const uint32 uIndex = pParent->GetIndex();
			pC = (*ppC) = ms_allocations[uIndex] ? &ms_components[uIndex] : NULL;
		}
		return pC;
	}

	//	This thing digs deep
	static ComponentType* GetComponentFromParentRecursive(ComponentType** ppC, const GameObject* pObj)
	{
		const GameObject* pParent = pObj->GetParent();
		ComponentType* pC = NULL;
		if(pParent)
		{
			const uint32 uIndex = pParent->GetIndex();
			pC = (*ppC) = ms_allocations[uIndex] ? &ms_components[uIndex] : NULL;
			if(pC == NULL)
			{
				pC = GetComponentFromParentRecursive(ppC, pParent);
			}
		}
		return pC;
	}

	static ComponentType* Create(GameObject* pObj)
	{
		pObj->SetChanged();
		const uint32 uIndex = pObj->GetIndex();
		ComponentType* pC = &ms_components[uIndex];
		ms_allocations[uIndex] = true;
		OnActivate(pC);
		return pC;
	}

	static void Free(GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		ms_allocations[uIndex] = false;
	}

	static void Init() 
	{ 
		ms_components = new ComponentType[GameObject::NumGameObjects];
		ms_allocations = new bool[GameObject::NumGameObjects];
		SDL_memset(ms_allocations, false, sizeof(bool) * GameObject::NumGameObjects);
	}

	static void RegisterLua(lua_State* pL){}
	static void OnActivate(ComponentType* pC){}
	static void OnDeactivate(ComponentType* pC){}
	
	static void Clear()
	{ 
		delete [] ms_components;
		delete [] ms_allocations;
	}

protected:
	static ComponentType* ms_components;
	static bool* ms_allocations;
};

template <class ComponentType>
ComponentType* Component<ComponentType>::ms_components = NULL;

template <class ComponentType>
bool* Component<ComponentType>::ms_allocations = NULL;

}	//	namespace neko
