/****************************************************************************
//	Filename: IMGHeader.h
//	Description: Header data file for loading binary textures originally saved 
//	as SDL_Surface
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

struct IMGHeader
{
	Uint32 rmask;
	Uint32 gmask;
	Uint32 bmask;
	Uint32 amask;
	int width;
	int height;
	int bpp;
	bool hasPalette;
};

struct IMGPalette
{
	SDL_Color color;
	int ncolor;
};

}	//	namespace neko
