/****************************************************************************
//	Filename: Time.h
//	Description: Windows implementations for time
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

class Time
{
public:
	static void Init();
	static void Shut();
	static uint32 GetTicks();
	static sint32 GetTickDiff(sint32 uStart, sint32 uEnd);
};

}	//	namespace neko
