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
	m_uStart = SDL_GetTicks();
}

uint32 Timer::GetElapsed()
{
	uint32 uNow = SDL_GetTicks();
	uint32 uDiff = (uNow - m_uStart);
	m_uStart = uNow;
	return uDiff;
}

}	//	namespace neko