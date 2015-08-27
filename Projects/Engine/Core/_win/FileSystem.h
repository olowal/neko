/****************************************************************************
//	Filename: FileSystem.h
//	Description: Win32 wrapper functions for files
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/DArray.h"
#include "Engine/Core/String.h"
namespace neko
{

class FileSystem
{
public:
	static void GetListOfFiles(const char* sPath, const char* sExtension, DArray<U8String>& list);

	static uint64 GetFileSize(const char* sFilename);
	static uint64 GetFileSize(const wchar_t* sFilename);

protected:

};

}	//	namespace neko
