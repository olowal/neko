//	TextureMgr.cpp
#include "TextureMgr.h"
#include "Engine/Graphics/GFXDevice.h"

static const wchar_t* s_sTextureFolderName = L"Data/Textures/";

namespace neko
{

TextureMgr::TextureMgr() :
m_textures(MAX_TEXTURES)
{
	
}

TextureMgr::~TextureMgr()
{
	m_textures.Clear();
}

bool TextureMgr::Init()
{
	return true;
}

SDL_Texture* TextureMgr::Load(const GFXDevice* pDevice, const char* szFilename)
{

	SDL_Texture* pTexture = DoesTextureExist(szFilename);

	if(pTexture != NULL)
	{
		pTexture = pDevice->LoadTextureFromBinary(szFilename);
		ASSERT(pTexture != NULL);
		Texture* pT = m_textures.Alloc();
		pT->Init(pTexture, szFilename);
	}

	return pTexture;
}

void TextureMgr::Unload(SDL_Texture* pTexture)
{
	for(auto it = m_textures.Begin(); !it.IsEnd(); ++it)
	{
		Texture* pT = (*it);

		if(pT->GetTexture() == pTexture)
		{
			m_textures.Free(pT);
			break;
		}
	}
}

void TextureMgr::Unload(const char* szName)
{
	for(auto it = m_textures.Begin(); !it.IsEnd(); ++it)
	{
		Texture* pT = (*it);

		if(pT->GetName().Equals(szName))
		{
			m_textures.Free(pT);
			break;
		}
	}
}

SDL_Texture* TextureMgr::DoesTextureExist(const char* szName)
{
	for(auto it = m_textures.Begin(); !it.IsEnd(); ++it)
	{
		Texture* pTexture = (*it);

		if(pTexture->GetName().Equals(szName))
		{
			return pTexture->GetTexture();
		}
	}

	return NULL;
}

}	//	namespace neko