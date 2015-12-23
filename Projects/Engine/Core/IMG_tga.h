/****************************************************************************
//	Filename: IMG_tga.h
//	Description: Load SDL_Surface from a tga file.
//	Uses TGA loader from SDL_image library
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Graphics/IMGHeader.h"
class IMG_tga
{
public:
	static SDL_Surface* Load(const char* pzFilename, neko::IMGHeader* pImgHeader);
};