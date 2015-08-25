/****************************************************************************
//	Filename: Common.h
//	Description: Common defines and includes not likely to change
*****************************************************************************/

#pragma once

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include "SDL2/SDL.h"
#undef main

#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <limits.h>
#include <direct.h>

#include <d2d1_2.h>
#include <d2d1_2helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "d2d1")

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "Engine/Debug/Debug.h"

typedef unsigned char		uint8;
typedef signed char			sint8;
typedef signed short		sint16;
typedef unsigned short		uint16;
typedef signed int			sint32;
typedef unsigned int		uint32;
typedef long long			sint64;
typedef unsigned long long	uint64;
typedef float				real;

typedef unsigned __int8		byte;
typedef unsigned __int16	word;
typedef unsigned __int32	dword;
typedef unsigned __int16	qword;

#define PRIVATE_COPY(NameOfClass)	NameOfClass(NameOfClass& xC) { ASSERT(false); } \
									NameOfClass& operator=(NameOfClass& xC)	{ ASSERT(false); return *this; }

namespace neko
{

template <class Interface>
inline void SafeRelease(Interface *&p)
{
	if(p != NULL)
	{
		p->Release();
		p = NULL;
	}
}

}	//	namespace neko