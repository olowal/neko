/****************************************************************************
//	Filename: StringUtils.h
//	Description: Helper functions for string operations.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/String.h"

namespace neko
{

namespace
{

//	reads through a string and removes everything in the path and file ending
void GetFilenameAsIs(const char* sFilepath, U8String& sFilename)
{
	char sTmp[MAX_PATH];
	strcpy(sTmp, sFilepath);
	int iLen = (int)strlen(sTmp);
	while(iLen > 0 && sTmp[iLen - 1] != '.')
	{
		iLen--;
	}

	if(iLen > 0)
	{
		sTmp[iLen - 1] = '\0';
	}

	while(iLen > 0 && sTmp[iLen - 1] != '/' && sTmp[iLen - 1] != '\\')
	{
		iLen--;
	}

	sFilename.Set(sTmp + iLen);
}

//	reads through a string and removes everything in the path and file ending (for wide char)
void GetFilenameAsIsW(const wchar_t* sFilepath, WString& sFilename)
{
	wchar_t sTmp[MAX_PATH];
	wcscpy(sTmp, sFilepath);
	int iLen = (int)wcslen(sTmp);
	while(iLen > 0 && sTmp[iLen - 1] != '.')
	{
		iLen--;
	}

	if(iLen > 0)
	{
		sTmp[iLen - 1] = '\0';
	}

	while(iLen > 0 && sTmp[iLen - 1] != '/' && sTmp[iLen - 1] != '\\')
	{
		iLen--;
	}

	sFilename.Set(sTmp + iLen);
}

}	//	anonymous namespace

}	//	namespace neko