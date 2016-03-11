/****************************************************************************
//	Filename: GameObject.h
//	Description: A game object is an identifier for components
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/ObjectPool.h"
#include "Engine/Core/LinkedList.h"

typedef struct lua_State lua_State;

namespace neko
{

class GameObject
{
public:
	GameObject();

	static const char* ScriptHandle;
	static const uint32 NumGameObjects;

	static GameObject* Alloc() { return ms_pool.Alloc(); }
	static void Free(GameObject* pObj);

	static bool Create(lua_State* pL, const char* szHandle);

	uint32 GetIndex() const { return m_uIndex; }

	void SetChanged();
	static void UpdateComponents();

	static void Init();
	static void Register(lua_State* pL);

private:
	static void SetIndex(GameObject* pObj);
	static ObjectPool<GameObject, false> ms_pool;
	static LinkedList<GameObject> ms_componentsToCheck;
	static LinkedList<GameObject> ms_getComponents;

	GameObject* m_pParent;
	uint32 m_uIndex;
	bool m_bChanged;
};

}	//	namespace neko
