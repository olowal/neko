/****************************************************************************
//	Filename: Color.h
//	Description: Color values
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class Color
{
public:
	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;

	static void Copy(SDL_Color& dst, SDL_Color& src)
	{
		dst.a = src.a;
		dst.b = src.b;
		dst.g = src.g;
		dst.r = src.r;
	}
       
};

}	//	namespace neko