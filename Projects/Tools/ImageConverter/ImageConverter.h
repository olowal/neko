/****************************************************************************
//	Filename: ImageConverter.h
//	Description: Converts image files to binay format
*****************************************************************************/

#pragma once

#include "Engine/Common/Common.h"

namespace neko
{

class ImageConverter
{
public:
	ImageConverter();
	~ImageConverter();

	void Convert();
private:
	SDL_Surface* TGAToBin(const char* sFilename, FILE* pFile);
	SDL_Texture* LoadTGA(SDL_Renderer* pRndr, const char* sFile);
};

}	//	namespace neko