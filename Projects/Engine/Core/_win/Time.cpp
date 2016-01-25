//	Time.cpp
#include "Engine/Core/_win/Time.h"

using namespace neko;

void neko::Time::Init()
{
	timeBeginPeriod(1);
}

void neko::Time::Shut()
{
	timeEndPeriod(1);
}

uint32 neko::Time::GetTicks()
{
	DWORD dwTime = ::timeGetTime();
	return static_cast<uint32>(dwTime);
}

sint32 neko::Time::GetTickDiff(sint32 iStart, sint32 iEnd)
{
	if(iEnd > iStart)
	{
		return iEnd - iStart;
	}
	
	sint64 iD = (static_cast<sint64>(2<<32) - iStart);
	iD += static_cast<sint64>(iEnd);
	return static_cast<sint32>(iD);
}
