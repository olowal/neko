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

	virtual bool Init();
	virtual void Shut();
	
	void Start();

protected:
	virtual void Run();
};

}	//	namespace neko