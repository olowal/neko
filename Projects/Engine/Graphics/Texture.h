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

	void Init(ID2D1Bitmap* pBitmap) { m_pBitmap = pBitmap; }

	void SetName(const String& name) { m_name.Set(name); }
	const WString& GetName() const { return m_name; }

	ID2D1Bitmap* GetBitmap() const { return m_pBitmap; }
private:
	WString m_name;
	ID2D1Bitmap* m_pBitmap;
};

}	//	namespace neko