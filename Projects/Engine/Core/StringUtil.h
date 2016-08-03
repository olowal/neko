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

//	Copy a part of a string into an empty buffer, returns the length of the string.
inline uint32 Copy(char* szDst, const char* szSrc, const uint32 uLength)
{
	uint32 uCount = 0;
	while(*szSrc && uCount < uLength)
	{
		*szDst++ = *szSrc++;
		uCount++;
	}
	*szDst = '\0';
	return uCount;
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

inline bool FirstOccurance(char* szDst, const char* szSrc, const char* szCmp)
{
	uint32 uCmpLen = neko::str::Length(szCmp);
	uint32 uSrcLen = neko::str::Length(szSrc);
	uint32 uC = 0;
	if(uCmpLen > 0 && uSrcLen > 0)
	{
		while((uC + uCmpLen) < uSrcLen)
		{
			if(strncmp(szSrc + uC, szCmp, uCmpLen) == 0)
			{
				neko::str::Copy(szDst, szSrc, uC);
				return true;
			}

			uC++;
		}
	}

	return false;
}

}	//	namespace str
}	//	namespace neko
