/****************************************************************************
//	Filename: FileSystem.h
//	Description: Win32 wrapper functions for files
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

class FileSystem
{
public:
	static uint32 GetListOfFiles(const char* sPath, const char* sExtension, char** ppsBuf, const uint32 uBufSize, const uint32 uStringSize);

	static uint64 GetFileSize(const char* sFilename);
	static uint64 GetFileSize(const wchar_t* sFilename);

protected:

};

}	//	namespace neko
