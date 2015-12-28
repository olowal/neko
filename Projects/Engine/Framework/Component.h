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
	static ComponentType* GetComponent(GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		ComponentType* pC = ms_allocations[uIndex] ? &ms_components[uIndex] : NULL;
		return pC;
	}

	static ComponentType* Create(GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		if(!ms_allocations[uIndex])
		{
			pObj->SetChanged();

			ComponentType* pC = &ms_components[uIndex];
			ms_allocated.AddToLast(pC);
			ms_allocations[uIndex] = true;
			OnActivate(pC);
			return pC;
		}

		return NULL;
	}

	static void Free(GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		if(ms_allocations[uIndex])
		{
			OnDeactivate(&ms_components[uIndex]);
			ms_allocated.Remove(&ms_components[uIndex]);
			ms_allocations[uIndex] = false;
			pObj->SetChanged();
		}
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
	static LinkedList<ComponentType> ms_allocated;
	static ComponentType* ms_components;
	static bool* ms_allocations;
};

template <class ComponentType>
LinkedList<ComponentType> Component<ComponentType>::ms_allocated;

template <class ComponentType>
ComponentType* Component<ComponentType>::ms_components = NULL;

template <class ComponentType>
bool* Component<ComponentType>::ms_allocations = NULL;

}	//	namespace neko
