//	FileSystem.cpp
#include "FileSystem.h"

namespace neko
{

void FileSystem::GetListOfFiles(const char* sPath, const char* sExtension, DArray<U8String>& list)
{
	WIN32_FIND_DATA data;
	ZeroMemory(&data, sizeof(WIN32_FIND_DATA));
	HANDLE hFind;

	char sFullPath[255];
	char sFile[255];
	strcpy_s(sFullPath, sPath);
	strcat_s(sFullPath, sExtension);
	hFind = FindFirstFileA(sFullPath, &data);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		strcpy_s(sFile, sPath);
		strcat_s(sFile, data.cFileName);
		U8String sT;
		sT.Set(sFile);
		list.Add(sT);
		while(FindNextFileA(hFind, &data) != 0)
		{
			sFile[0] = '\0';
			strcpy_s(sFile, sPath);
			strcat_s(sFile, data.cFileName);
			sT.Set(sFile);
			list.Add(sT);
		}
	}
}

uint64 FileSystem::GetFileSize(const char* sFilename)
{
	WIN32_FILE_ATTRIBUTE_DATA data;
	if(!GetFileAttributesExA(sFilename, GetFileExInfoStandard, &data))
	{
		return (uint64)0;
	}

	LARGE_INTEGER size;
	size.HighPart = data.nFileSizeHigh;
	size.LowPart = data.nFileSizeLow;
	return (uint64)size.QuadPart;
}

uint64 FileSystem::GetFileSize(const wchar_t* sFilename)
{
	WIN32_FILE_ATTRIBUTE_DATA data;
	if(!GetFileAttributesExW(sFilename, GetFileExInfoStandard, &data))
	{
		return (uint64)0;
	}

	LARGE_INTEGER size;
	size.HighPart = data.nFileSizeHigh;
	size.LowPart = data.nFileSizeLow;
	return (uint64)size.QuadPart;
}

}	//	namespace neko