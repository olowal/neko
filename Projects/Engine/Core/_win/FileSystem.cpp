//	FileSystem.cpp
#include "FileSystem.h"

namespace neko
{

uint32 FileSystem::GetListOfFiles(const char* sPath, const char* sExtension, char** ppsBuf, const uint32 uBufSize, const uint32 uStringSize)
{
	WIN32_FIND_DATA data;
	ZeroMemory(&data, sizeof(WIN32_FIND_DATA));
	HANDLE hFind;

	char sFullPath[255];
	char sFile[255];
	strcpy_s(sFullPath, sPath);
	strcat_s(sFullPath, sExtension);
	hFind = FindFirstFileA(sFullPath, &data);
	uint32 uCount = 0;

	if(hFind != INVALID_HANDLE_VALUE)
	{
		strcpy_s(sFile, sPath);
		strcat_s(sFile, data.cFileName);
		char* pS = &ppsBuf[uCount++][0];
		strcpy_s(pS, uStringSize, sFile);

		while(FindNextFileA(hFind, &data) != 0 && uCount < uBufSize)
		{
			sFile[0] = '\0';
			strcpy_s(sFile, sPath);
			strcat_s(sFile, data.cFileName);
			pS = &ppsBuf[uCount++][0];
			strcpy_s(pS, uStringSize, sFile);
		}
	}

	return uCount;
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