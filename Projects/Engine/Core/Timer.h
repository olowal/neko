/****************************************************************************
//	Filename: Timer.h
//	Description: Basic timer class, only counts milliseconds
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
	uint32 m_uStart;
};

}	//	namespace neko