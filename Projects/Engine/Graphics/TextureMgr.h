/****************************************************************************
//	Filename: TextureMgr.h
//	Description: Texture manager, contains lots of different textures.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/ObjectPool.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Core/ISingleton.h"

namespace neko
{

class GFXDevice;
class TextureMgr
{
public:
	TextureMgr();
	~TextureMgr();

	bool Init();

	Texture* Load(const wchar_t* szFilename, const GFXDevice* pDevice);
	void Unload(Texture* pTexture);

	enum { MAX_TEXTURES = 64 };

private:
	Texture* DoesTextureExist(const WString& sName);

	ObjectPool<Texture> m_textures;
	IWICImagingFactory* m_pIWICFactory;
};

}	//	namespace neko