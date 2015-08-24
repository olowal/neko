//	TextureMgr.cpp
#include "TextureMgr.h"
#include "Engine/Graphics/GFXDevice.h"

static const wchar_t* s_sTextureFolderName = L"Data/Textures/";

namespace neko
{

TextureMgr::TextureMgr() :
m_textures(MAX_TEXTURES)
{
	m_pIWICFactory = NULL;
}

TextureMgr::~TextureMgr()
{
	SafeRelease(m_pIWICFactory);
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
	WString sFile;
	wchar_t sPath[MAX_PATH];
	wcscpy_s(sPath, s_sTextureFolderName);
	wcscat_s(sPath, szFilename);

	sFile.Set(szFilename);
	Texture* pTexture = DoesTextureExist(sFile);

	if(pTexture != NULL)
	{
		return pTexture;
	}

	ASSERT(m_pIWICFactory != NULL);
	IWICBitmapDecoder* pDecoder = NULL;
	HRESULT hr = m_pIWICFactory->CreateDecoderFromFilename(sPath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
	ASSERT(SUCCEEDED(hr));

	IWICBitmapFrameDecode* pFrame = NULL;

	hr = pDecoder->GetFrame(0, &pFrame);
	ASSERT(SUCCEEDED(hr));

	IWICFormatConverter* pFormatConverter = NULL;
	hr = m_pIWICFactory->CreateFormatConverter(&pFormatConverter);
	ASSERT(SUCCEEDED(hr));

	hr = pFormatConverter->Initialize(
		pFrame, 
		GUID_WICPixelFormat32bppPBGRA, 
		WICBitmapDitherTypeNone, 
		NULL, 
		0.0f, 
		WICBitmapPaletteTypeCustom
		);

	ASSERT(SUCCEEDED(hr));
	
	ID2D1Bitmap* pBitmap = pDevice->CreateBitmapFromWicBitmap(pFormatConverter);
	ASSERT(pBitmap != NULL);

	pTexture = m_textures.Alloc();
	pTexture->Init(pBitmap);

	return NULL;
}

void TextureMgr::Unload(Texture* pTexture)
{
	m_textures.Free(pTexture);
}

Texture* TextureMgr::DoesTextureExist(const WString& sName)
{
	ObjectPool<Texture>::Iterator it = m_textures.Begin();
	for(; !it.IsEnd(); ++it)
	{
		Texture* pTexture = (*it);

		if(pTexture->GetName() == sName)
		{
			return pTexture;
		}
	}

	return NULL;
}

}	//	namespace neko