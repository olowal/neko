/****************************************************************************
//	Filename: Texture.h
//	Description: Holder of a texture
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class Texture
{
public:
	Texture(){}
	~Texture(){}

private:
	ID2D1Bitmap* m_pBitmap;
};

}	//	namespace neko