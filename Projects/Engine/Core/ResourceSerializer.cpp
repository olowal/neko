//	ResourceSerializer.cpp
#include "ResourceSerializer.h"
#include "Engine/Graphics/IMGHeader.h"
#include "Engine/Core/String.h"
#include "Engine/Core/StringCRC.h"
#include "Engine/Core/FileSystem.h"
#include "Engine/Graphics/Color.h"
#include "IMG_tga.h"

namespace neko
{

static const char* s_szWatermark = "neko_bin";	//	each bin file begine with this so we can verify what we open

void ResourceSerializer::SerializeToBinary(const char* szReadPath, const char* szSavePath, const char* szFilename)
{
	FileSystem::FileData fileData(255);
	FileSystem::GetListOfFiles(szReadPath, "*.tga", fileData);

	SDL_RWops* pRW = NULL;

	if(szSavePath != NULL)
	{
		const size_t uSize = 255;
		char sFullPath[uSize];
		SDL_strlcpy(sFullPath, szSavePath, uSize);
		SDL_strlcat(sFullPath, szFilename, uSize);
		pRW = SDL_RWFromFile(sFullPath, "wb");
	}
	else
	{
		pRW = SDL_RWFromFile(szFilename, "wb");
	}

	ASSERT(pRW != NULL);
	SDL_RWwrite(pRW, &s_szWatermark[0], SDL_strlen(s_szWatermark) * sizeof(char), 1);

	for(auto it = fileData.Begin(); !it.IsEnd(); ++it)
	{
		IMGHeader imgHeader;
		SDL_Surface* pSurface = IMG_tga::Load((*it), &imgHeader);
		if(pSurface != NULL)
		{
			imgHeader.hasPalette = pSurface->format->palette != NULL ? true : false;

			U8String sName;
			str::GetFilenameAsIs((*it), sName);
			StringCRC hash(sName.CStr());
			int iSize = (imgHeader.width * imgHeader.height) * 4;
			uint32 uHashName = hash.Get();
			uint32 uBlockSize = (uint32)(sizeof(neko::IMGHeader) + ((size_t)iSize) * sizeof(Uint8)) + (imgHeader.hasPalette ? sizeof(neko::IMGPalette) : (size_t)0);
			
			SDL_RWwrite(pRW, &uBlockSize, sizeof(uint32), 1);
			SDL_RWwrite(pRW, &uHashName, sizeof(uint32), 1);
			SDL_RWwrite(pRW, &imgHeader, sizeof(neko::IMGHeader), 1);

			if(imgHeader.hasPalette)
			{
				IMGPalette palette;
				palette.ncolor = pSurface->format->palette->ncolors;
				Color::Copy(palette.color, *pSurface->format->palette->colors);

				SDL_RWwrite(pRW, &palette, sizeof(neko::IMGPalette), 1);
			}
			
			SDL_RWwrite(pRW, pSurface->pixels, iSize * sizeof(Uint8), 1);
		}
	}

	uint32 uEnd = 0;
	SDL_RWwrite(pRW, &uEnd, sizeof(uint32), 1);

	SDL_RWclose(pRW);
}

SDL_Texture* ResourceSerializer::LoadTextureFromBinary(SDL_Renderer* pRndr, const char* szFilename, const char* szBinaryFilename)
{
	SDL_Texture* pTexture = NULL;
	SDL_RWops* pRW = SDL_RWFromFile(szBinaryFilename, "rb");

	ASSERT(pRW != NULL);

	{
		char sWatermark[16];
		const size_t uLen = SDL_strlen(s_szWatermark);
		SDL_RWread(pRW, sWatermark, uLen * sizeof(char), 1);
		sWatermark[uLen] = '\0';

		if(SDL_strcmp(sWatermark, s_szWatermark) != 0)
		{
			return NULL;
		}
	}

	uint32 uHashName = StringCRC::GetCRC(szFilename);
	uint32 uBlockSize = 0;
	uint32 uHash;

	SDL_RWread(pRW, &uBlockSize, sizeof(uint32), 1);

	while(uBlockSize != 0)
	{
		SDL_RWread(pRW, &uHash, sizeof(uint32), 1);

		if(uHash == uHashName)
		{
			neko::IMGHeader img;
			SDL_RWread(pRW, &img, sizeof(neko::IMGHeader), 1);

			SDL_Surface* pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, img.width, img.height,
				img.bpp * 8,
				img.rmask, img.gmask, img.bmask, img.amask);

			if(img.hasPalette)
			{
				neko::IMGPalette palette;
				SDL_RWread(pRW, &palette, sizeof(neko::IMGPalette), 1);

				SDL_Palette* pPalette = pSurface->format->palette;
				pPalette->ncolors = palette.ncolor;
				Color::Copy(*pPalette->colors, palette.color);
			}

			SDL_RWread(pRW, pSurface->pixels, ((img.width * img.height) * 4) * sizeof(Uint8), 1);
			
			pTexture = SDL_CreateTextureFromSurface(pRndr, pSurface);

			ASSERT(pTexture != NULL);

			uBlockSize = 0;	// exit the loop
		}
		else
		{
			SDL_RWseek(pRW, uBlockSize, SEEK_CUR);
			SDL_RWread(pRW, &uBlockSize, sizeof(uint32), 1);
		}
	}

	SDL_RWclose(pRW);

	return pTexture;
}

SDL_Surface* ResourceSerializer::LoadTGA(const char* szFilename)
{
	return IMG_tga::Load(szFilename, NULL);
}

SDL_Texture* ResourceSerializer::LoadTGA(SDL_Renderer* pRndr, const char* szFilename)
{
	SDL_Surface* pSurface = IMG_tga::Load(szFilename, NULL);

	if(pSurface != NULL)
	{
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRndr, pSurface);
	}

	return NULL;
}

}	//	namespace neko
