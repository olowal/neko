/****************************************************************************
//	Filename: TextureMgr.h
//	Description: Texture manager, contains lots of different textures.
*****************************************************************************/
#include "Engine/Common/Common.h"

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

private:
	IWICImagingFactory* m_pIWICFactory;
};

}	//	namespace neko