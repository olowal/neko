//	Timer.cpp

#include "Timer.h"

namespace neko
{

Timer::Timer()
{
	Reset();
}

Timer::~Timer(){}

void Timer::Reset()
{
	m_uStart = ::timeGetTime();
}

uint32 Timer::GetElapsed()
{
	dword dwNow = ::timeGetTime();
	dword dwDiff = (dwNow - m_uStart);
	m_uStart = dwNow;
	return static_cast<uint32>(dwDiff);
}

}	//	namespace neko