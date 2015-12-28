/****************************************************************************
//	Filename: System.h
//	Description: Interface for system
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/ComponentManager.h"
#include "Engine/Framework/GameObject.h"
#include "Engine/Core/LinkedList.h"
namespace neko
{

template <class SystemType>
class System
{
	typedef typename SystemType::Components Components;
public:
	static void Init() 
	{ 
		ms_components = new Components [GameObject::NumGameObjects];
		SDL_memset(ms_components, NULL, sizeof(Components) * GameObject::NumGameObjects);
		ms_active = new bool[GameObject::NumGameObjects];
		SDL_memset(ms_active, false, sizeof(bool) * GameObject::NumGameObjects);
	}
	
	static void Clear() 
	{ 
		delete [] ms_components;
		delete [] ms_active;
	}

	static void GetComponents(GameObject* pObj)
	{
		const uint32 uIndex = pObj->GetIndex();
		Components* pC = &ms_components[uIndex];
		
		if(SystemType::GetComponents(pObj, pC))
		{
			if(!ms_active[uIndex])
			{
				ms_systems.AddToLast(pC);
				ms_active[uIndex] = true;
			}
		}
		else if(ms_active[uIndex])
		{
			ms_systems.Remove(pC);
			ms_active[uIndex] = false;
		}
	}

	static void Run(const float fDt)
	{
		for(auto it = ms_systems.Begin(); !it.IsEnd(); ++it)
		{
			Components* pC = (*it);
			SystemType::Run(pC, fDt);
		}
	}

private:
	static Components* ms_components;
	static bool* ms_active;
	static LinkedList<Components> ms_systems;
};

template <class SystemType>
typename SystemType::Components* System<SystemType>::ms_components = NULL;

template <class SystemType>
bool* System<SystemType>::ms_active = NULL;

template <class SystemType>
LinkedList<typename SystemType::Components> System<SystemType>::ms_systems;

}	//	namespace neko
