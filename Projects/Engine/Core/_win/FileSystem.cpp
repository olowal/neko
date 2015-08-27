//	FileSystem.cpp
#include "FileSystem.h"

namespace neko
{

FileSystem::FileData::FileData(uint32 uSize, uint32 uMaxPath)
{
	m_uSize = uSize;
	m_uMaxPath = uMaxPath;
	m_ppFiles = new char*[uSize];

	for(uint32 i = 0; i < uSize; i++)
	{
		m_ppFiles[i] = new char[uMaxPath];
	}
}

FileSystem::FileData::~FileData()
{
	for(uint32 i = 0; i < m_uSize; i++)
	{
		delete [] m_ppFiles[i];
	}

	delete [] m_ppFiles;
}

void FileSystem::FileData::Add(const char* sFilename)
{
	strcpy_s(&m_ppFiles[m_uCount++][0], m_uMaxPath, sFilename);
}

uint32 FileSystem::GetListOfFiles(const char* sPath, const char* sExtension, FileSystem::FileData& fileData)
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
		fileData.Add(sFile);

		while(FindNextFileA(hFind, &data) != 0)
		{
			sFile[0] = '\0';
			strcpy_s(sFile, sPath);
			strcat_s(sFile, data.cFileName);
			fileData.Add(sFile);
		}
	}

	FindClose(hFind);

	return uCount;
}

uint32 FileSystem::GetListOfFolders(const char* sPath, char** ppsBuf, const uint32 uBufSize, const uint32 uStringSize)
{
	WIN32_FIND_DATA data;
	ZeroMemory(&data, sizeof(WIN32_FIND_DATA));
	HANDLE hFind = FindFirstFileA(sPath, &data);

	do
	{
		if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//	Add it here
		}
	} while(FindNextFileA(hFind, &data) != 0);

	return 0;
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