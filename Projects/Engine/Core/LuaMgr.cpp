//	LuaMgr.cpp
#include "LuaMgr.h"
#include "Engine/Core/FileSystem.h"
namespace neko
{

void LuaMgr::LoadFiles(const char* szPath) const
{
	FileSystem::FileData files(255);
	FileSystem::GetListOfFiles(szPath, "*.lua", files);

	for(auto it = files.Begin(); !it.IsEnd(); ++it)
	{
		ExecuteFile((*it));
	}
}

void LuaMgr::ExecuteFile(const char* szFilename) const
{
	int iState = luaL_loadfile(m_L, szFilename);
	Error(iState);
	iState = lua_pcall(m_L, 0, 0, 0);
	Error(iState);
}

void LuaMgr::ExecuteString(const char* szString) const
{
	int iState = luaL_dostring(m_L, szString);
	Error(iState);
}

void LuaMgr::Error(int iError) const
{
	if(iError != 0)
	{
		const char* sError = lua_tostring(m_L, -1);
		printf("%s\n", sError);
		lua_pop(m_L, 1);
	}
}

}	//	namespace neko
