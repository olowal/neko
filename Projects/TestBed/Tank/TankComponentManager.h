/****************************************************************************
//	Filename: TankComponentManger.h
//	Description: Inherits from ComponentManager, adds initialization and runs
//	Systems designed for Tank project.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/ComponentManager.h"
class TankComponentManager : public neko::ComponentManager
{
	typedef neko::ComponentManager Inherited;
public:
	virtual void Init(lua_State* pL);
	virtual void Shut();
	virtual void Run(const float fDt);
private:

};
