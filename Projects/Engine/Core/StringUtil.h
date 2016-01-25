/****************************************************************************
//	Filename: StringUtil.h
//	Description: Helper functions for string manipulations
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{
namespace str
{

//	Get length of a string
inline uint32 Length(const char* szStr)
{
	uint32 uLength = 0;
	while(*szStr++)
	{
		uLength++;
	}
	return uLength;
}
//	Copy a string into an empty buffer, returns the length of the string.
inline uint32 Copy(char* szDst, const char* szSrc)
{
	uint32 uLength = 0;
	while(*szSrc)
	{
		*szDst++ = *szSrc++;
		uLength++;
	}
	*szDst = '\0';
	return uLength;
}
//	Append one string after another. Returns the length of the new string
inline uint32 Concatenate(char* szDst, const char* szSrc)
{
	uint32 uLength = neko::str::Length(szDst) ;
	uLength = neko::str::Copy(szDst + uLength, szSrc);
	return uLength;
}

//	Append one string after another, pass the length of the source
inline uint32 Concatenate(char* szDst, const char* szSrc, uint32 uSrcLen)
{
	uint32 uLength = neko::str::Copy(szDst + uSrcLen, szSrc) + uSrcLen;
	return uLength;
}

}	//	namespace str
}	//	namespace neko
