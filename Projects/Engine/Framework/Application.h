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
	void Run();

protected:
	//	Overload these member functions in your own class
	virtual bool OnInit(){ return true; }
	virtual void OnShut(){}

	virtual void OnRun() = 0;
	virtual bool ShouldQuit() = 0;
	virtual bool MessagePump() = 0;

	uint32 GetTick() const;
	uint32 GetTickDiff(uint32 uStart, uint32 )

private:
	float m_fFPS;
	int m_iMS;
};

}	//	namespace neko