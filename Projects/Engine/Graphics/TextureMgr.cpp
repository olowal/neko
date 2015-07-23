//	TextureMgr.cpp
#include "TextureMgr.h"

namespace neko
{

TextureMgr::TextureMgr() :
m_textures(MAX_TEXTURES)
{
	m_pIWICFactory = NULL;
}

TextureMgr::~TextureMgr()
{
	SafeRelease(&m_pIWICFactory);
}

bool TextureMgr::Init()
{
	HRESULT hr = S_OK;
	hr = CoCreateInstance(
	CLSID_WICImagingFactory,
	NULL,
	CLSCTX_INPROC_SERVER,
	IID_PPV_ARGS(&m_pIWICFactory)
	);

	return SUCCEEDED(hr);
}

Texture* TextureMgr::Load(const wchar_t* szFilename, const GFXDevice* pDevice)
{
	ASSERT(m_pIWICFactory != NULL);
	IWICBitmapDecoder* pDecorder = NULL;
	HRESULT hr = m_pIWICFactory->CreateDecoderFromFilename(szFilename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecorder);
	ASSERT(SUCCEEDED(hr));

}

void TextureMgr::Unload(Texture* pTexture)
{

}

}	//	namespace neko