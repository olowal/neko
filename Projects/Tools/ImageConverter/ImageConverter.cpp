//	ImageConverter.cpp

#include "ImageConverter.h"
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include <direct.h>

namespace neko
{

ImageConverter::ImageConverter(){}
ImageConverter::~ImageConverter(){}

void ImageConverter::Convert()
{
	{
		//	Set the application path to the executable path
		wchar_t sT[MAX_PATH];
		::GetModuleFileNameW(NULL, sT, MAX_PATH);
		int iP = lstrlenW(sT);
		
		while(iP > 0
			&& (sT[iP - 1] != L'/')
			&& (sT[iP] != L'\\'))
		{
			iP--;
		}

		sT[iP] = L'\0';
		_wchdir(sT);
	}
}

}	//	namespace neko