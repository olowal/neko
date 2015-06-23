/****************************************************************************
//	Filename: Application.h
//	Description: Base of an application
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class Application
{
public:
	Application();
	virtual ~Application();

	bool Init();
	void Shut();
	virtual void Run() = 0;

	dword GetTick() const;
	dword GetTickDiff(dword dwStart, dword dwEnd) const;
protected:
	//	Overload these member functions in your own class
	virtual bool OnInit(){ return true; }
	virtual void OnShut(){}
};

}	//	namespace neko