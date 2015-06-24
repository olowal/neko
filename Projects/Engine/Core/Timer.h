/****************************************************************************
//	Filename: Timer.h
//	Description: Basic timer class
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class Timer
{
public:
	Timer();
	~Timer();

	void Reset();
	uint32 GetElapsed();

private:
	dword m_uStart;
};

}	//	namespace neko