/****************************************************************************
//	Filename: Debug.h
//	Description: Useful functions etc for debug
*****************************************************************************/

#pragma once

#include <intrin.h>

#ifdef assert
#undef assert
#endif

#ifndef FINAL_BUILD
#ifdef ASSERT
#undef ASSERT
#endif
inline void ASSERT(bool bCondition)
{
	if(!bCondition)
	{
		__debugbreak();
	}
}
#endif
