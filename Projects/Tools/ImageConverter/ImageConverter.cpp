//	ImageConverter.cpp

#include "ImageConverter.h"

namespace neko
{

static const char* s_sFolder = "../../../Data/";
static const char* s_sTextures = "Textures/";

ImageConverter::ImageConverter(){}
ImageConverter::~ImageConverter(){}

void ImageConverter::Convert()
{
	FILE* file = NULL;
	fopen_s(&file, "test.bin", "wb");

	const char* sFile = "Pikachu_Sprite.tga";
	const size_t uMaxPath = 255;
	char sPath[uMaxPath];
	SDL_strlcpy(sPath, s_sFolder, uMaxPath);
	SDL_strlcat(sPath, s_sTextures, uMaxPath);
	SDL_strlcat(sPath, sFile, uMaxPath);
	SDL_Surface* pSurface = TGAToBin(sPath, file);

	fclose(file);

	int p = 0;
	p++;
}

}	//	namespace neko