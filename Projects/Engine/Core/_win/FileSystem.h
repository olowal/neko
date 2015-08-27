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
	class FileData
	{
	public:
		FileData(uint32 uSize, uint32 uMaxPath = 255);
		~FileData();

		class Iterator
		{
		public:
			Iterator(char** ppFiles, uint32 uCount) : 
				m_ppFiles(ppFiles),
				m_uCount(uCount),
				m_uCurrent(0){}
		Iterator& operator++() { m_uCurrent++; return *this; }
		const char* operator*() const { return &m_ppFiles[m_uCurrent][0]; }
		char* operator*() { return &m_ppFiles[m_uCurrent][0]; }
		bool IsEnd() const { return m_uCurrent >= m_uCount; }
		private:
			char** m_ppFiles;
			uint32 m_uCount;
			uint32 m_uCurrent;
		};

		void Add(const char* sFilename);
		Iterator Begin() const { return Iterator(m_ppFiles, m_uCount); }

	private:
		char** m_ppFiles;
		uint32 m_uCount;
		uint32 m_uSize;
		uint32 m_uMaxPath;
	};

	static void GetListOfFiles(const char* sPath, const char* sExtension, FileSystem::FileData& fileData);
	static void GetListOfFolders(const char* sPath, FileSystem::FileData& fileData);

	static uint64 GetFileSize(const char* sFilename);
	static uint64 GetFileSize(const wchar_t* sFilename);

protected:

};

}	//	namespace neko
