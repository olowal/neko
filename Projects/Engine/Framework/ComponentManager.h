/****************************************************************************
//	Filename: ComponentManager.h
//	Description: 
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
typedef struct lua_State lua_State;
namespace neko
{

class GameObject;
class ComponentManager
{
public:
	ComponentManager();
	virtual ~ComponentManager();

	virtual void Init(lua_State* pL);
	virtual void Shut();
	virtual void Run(float fDelta);

	void Free(GameObject* pObj);

	static void GetComponents(GameObject* pObj);
};

}	//	namespace neko
