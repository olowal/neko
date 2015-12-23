/****************************************************************************
//	Filename: ResourceSerializer.h
//	Description: loads resources from data.bin. Only handles textures at this 
//	moment
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

class ResourceSerializer
{
public:
	static SDL_Surface* LoadTGA(const char* szFilename);
	static SDL_Texture* LoadTGA(SDL_Renderer* pRndr, const char* szFilename);
	static SDL_Texture* LoadTextureFromBinary(SDL_Renderer* pRndr, const char* szFilename, const char* szBinaryFilename = "data.bin");

	//	Loads all tga textures in the given path and puts them all into one binary file
	//	szReadPath:	What folder to read from
	//	szSavePath:	Where to save the binary file
	//	szFilename: Name of the binary file (default: data.bin)
	static void SerializeToBinary(const char* szReadPath, const char* szSavePath, const char* szFilename = "data.bin");
};

}	//	namespace neko
