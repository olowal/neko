//	ImageConverter.cpp

#include "ImageConverter.h"
#include "Engine/Core/FileSystem.h"
#include "Engine/Graphics/IMGHeader.h"

namespace neko
{

//static const char* s_sFolder = "../../../Data/";
static const char* s_sFolder = "Data/";
static const char* s_sTextures = "Textures/";

ImageConverter::ImageConverter(){}
ImageConverter::~ImageConverter(){}

void ImageConverter::Convert()
{
	FILE* file = NULL;
	fopen_s(&file, "_data/textures.bin", "wb");

	const char* sFile = "Pikachu_Sprite.tga";
	const uint32 uMaxPath = 255;
	char sPath[uMaxPath];
	SDL_strlcpy(sPath, s_sFolder, uMaxPath);
	SDL_strlcat(sPath, s_sTextures, uMaxPath);

	FileSystem::FileData fileData(64);
	FileSystem::GetListOfFiles(sPath, "*.tga", fileData);

	auto it = fileData.Begin();
	for(; !it.IsEnd(); ++it)
	{
		char sFilename[uMaxPath];
		SDL_strlcpy(sFilename, (*it), uMaxPath);
		SDL_Surface* pSurface = TGAToBin(sFilename, file);
		printf("%s\n", (*it));
	}

	uint32 uTerminate = 0;
	fwrite(&uTerminate, sizeof(uint32), 1, file);	//	end of resource bin
	fclose(file);

	fopen_s(&file, "_data/textures.bin", "rb");

	IMGHeader header;
	IMGPalette palette;
	uint32 uHashName = 0;
	uint32 uBlockSize = 0;
	void* pPixels = NULL;

	fread_s(&uBlockSize, sizeof(uint32),sizeof(uint32), 1, file);

	while(uBlockSize != 0)
	{
		fread_s(&uHashName, sizeof(uint32),sizeof(uint32), 1, file);
		fread_s(&header, sizeof(IMGHeader),sizeof(IMGHeader), 1, file);
		
		printf("Writing data\n");
		printf("block size %u hash: %u\n", uBlockSize, uHashName);

		SDL_Surface* pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, header.width, header.height, header.bpp * 8,
			header.rmask, header.gmask, header.bmask, header.amask);
		uint32 uSize = header.height * header.width;
		fread_s(pSurface->pixels, uSize, uSize, 1, file);
		fread_s(&uBlockSize, sizeof(uint32),sizeof(uint32), 1, file);
	}

	//fread_s(&pPixels, uSize, uSize)

	fclose(file);
}

}	//	namespace neko