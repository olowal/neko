/****************************************************************************
//	Filename: TextureMgr.h
//	Description: Texture manager, contains lots of different textures.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/ObjectPool.h"
#include "Engine/Graphics/Texture.h"

namespace neko
{

class GFXDevice;
class TextureMgr
{
public:
	TextureMgr();
	~TextureMgr();

	bool Init();

	SDL_Texture* Load(const GFXDevice* pDevice, const char* szFilename);
	void Unload(SDL_Texture* pTexture);
	void Unload(const char* szFilename);

	enum { MAX_TEXTURES = 64 };

private:
	SDL_Texture* DoesTextureExist(const char* szName);

	ObjectPool<Texture> m_textures;
};

}	//	namespace neko