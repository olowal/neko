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

	void SetName(const String& name) { m_name.Set(name); }
	const String& GetName() const { return m_name; }

	ID2D1Bitmap* GetBitmap() const { return m_pBitmap; }
private:
	String m_name;
	ID2D1Bitmap* m_pBitmap;
};

}	//	namespace neko