//	LuaVM.cpp
#include "LuaVM.h"
#include "Engine/Core/FileSystem.h"
namespace neko
{

void LuaVM::LoadFiles(const char* szPath) const
{
	FileSystem::FileData files(255);
	FileSystem::GetListOfFiles(szPath, "*.lua", files);

	for(auto it = files.Begin(); !it.IsEnd(); ++it)
	{
		ExecuteFile((*it));
	}
}

void LuaVM::ExecuteFile(const char* szFilename) const
{
	int iState = luaL_loadfile(m_L, szFilename);
	Error(iState);
	iState = lua_pcall(m_L, 0, 0, 0);
	Error(iState);
}

void LuaVM::ExecuteString(const char* szString) const
{
	int iState = luaL_dostring(m_L, szString);
	Error(iState);
}

void LuaVM::Error(int iError) const
{
	if(iError != 0)
	{
		const char* sError = lua_tostring(m_L, -1);
		printf("%s\n", sError);
		lua_pop(m_L, 1);
	}
}

void LuaVM::Init()
{
	Shut();
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
}

void LuaVM::Shut()
{
	if(m_L)
	{
		lua_close(m_L);
	}
}

}	//	namespace neko
