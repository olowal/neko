/****************************************************************************
//	Filename: Texture.h
//	Description: Holder of a texture
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/String.h"

namespace neko
{

class Texture
{
public:
	Texture(){}
	~Texture(){}

	void Init(SDL_Texture* pTexture, const char* szName) 
	{ 
		m_pTexture = pTexture; 
		m_name.Set(szName);
	}

	const U8String& GetName() const { return m_name; }
	SDL_Texture* GetTexture() const { return m_pTexture; }
private:
	U8String m_name;
	SDL_Texture* m_pTexture;
};

}	//	namespace neko