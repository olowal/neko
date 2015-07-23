/****************************************************************************
//	Filename: TextureMgr.h
//	Description: Texture manager, contains lots of different textures.
*****************************************************************************/
#include "Engine/Common/Common.h"
#include "Engine/Core/String.h"
#include "Engine/Core/ObjectPool.h"

namespace neko
{

class Texture;
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
	bool DoesTextureExist(const String& sName);

	ObjectPool<Texture> m_textures;
	IWICImagingFactory* m_pIWICFactory;
};

}	//	namespace neko